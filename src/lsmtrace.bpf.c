/*
 * Copyright 2020 Google LLC
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "lsmtrace.h"

struct {
	__uint(type, BPF_MAP_TYPE_RINGBUF);
	__uint(max_entries, 1 << 24);
} ringbuf SEC(".maps");

long ringbuffer_flags = 0;


//  Security hooks for program execution operations. 

SEC("lsm/bprm_creds_for_exec")
int BPF_PROG(bprm_creds_for_exec, struct linux_binprm *bprm)
{
	bpf_printk("lsm_hook: exec: bprm_creds_for_exec\n");
	return 0;
}

SEC("lsm/bprm_creds_from_file")
int BPF_PROG(bprm_creds_from_file, struct linux_binprm *bprm, struct file *file)
{
	bpf_printk("lsm_hook: exec: bprm_creds_from_file\n");
	return 0;
}

SEC("lsm/bprm_check_security")
int BPF_PROG(bprm_check_security, struct linux_binprm *bprm)
{
	bpf_printk("lsm_hook: exec: bprm_check_security\n");
	return 0;
}


SEC("lsm/bprm_committing_creds")
void BPF_PROG(bprm_committing_creds, struct linux_binprm *bprm)
{
	bpf_printk("lsm_hook: exec: bprm_committing_creds\n");
}

SEC("lsm/bprm_committed_creds")
void BPF_PROG(bprm_committed_creds, struct linux_binprm *bprm)
{
	bpf_printk("lsm_hook: exec: bprm_committed_creds\n");
}


// Security hooks for mount using fs_context.

SEC("lsm/fs_context_dup")
int BPF_PROG(fs_context_dup,  struct fs_context *fc, struct fs_context *src_sc)
{
	bpf_printk("lsm_hook: fs_context: fs_context_dup\n");
	return 0;
}

SEC("lsm/fs_context_parse_param")
int BPF_PROG(fs_context_parse_param, struct fs_context *fc, struct fs_parameter *param)
{
	bpf_printk("lsm_hook: fs_context: fs_context_parse_param\n");
	return 0;
}


// Security hooks for filesystem operations.

SEC("lsm/sb_alloc_security")
int BPF_PROG(sb_alloc_security, struct super_block *sb)
{
	bpf_printk("lsm_hook: fs: sb_alloc_security\n");
	return 0;
}

SEC("lsm/sb_free_security")
void BPF_PROG(sb_free_security, struct super_block *sb)
{
	bpf_printk("lsm_hook: fs: sb_free_security\n");
}

SEC("lsm/sb_free_mnt_opts")
void BPF_PROG(sb_free_mnt_opts, void *mnt_opts)
{
	bpf_printk("lsm_hook: fs: sb_free_mnt_opts\n");
}

SEC("lsm/sb_eat_lsm_opts")
int BPF_PROG(sb_eat_lsm_opts, char *orig, void **mnt_opts)
{
	bpf_printk("lsm_hook: fs: sb_eat_lsm_opts\n");
	return 0;
}

SEC("lsm/sb_statfs")
int BPF_PROG(sb_statfs, struct dentry *dentry)
{
	bpf_printk("lsm_hook: fs: sb_statfs\n");
	return 0;
}

SEC("lsm/sb_mount")
int BPF_PROG(sb_mount, const char *dev_name, const struct path *path,
	const char *type, unsigned long flags, void *data)
{
	bpf_printk("lsm_hook: fs: sb_mount\n");
	return 0;
}

// @sb_copy_data

SEC("lsm/sb_remount")
int BPF_PROG(sb_remount, struct super_block *sb, void *mnt_opts)
{
	bpf_printk("lsm_hook: fs: sb_mount\n");
	return 0;
}

SEC("lsm/sb_kern_mount")
int BPF_PROG(sb_kern_mount, struct super_block *sb)
{
	bpf_printk("lsm_hook: fs: sb_kern_mount\n");
	return 0;
}

SEC("lsm/sb_show_options")
int BPF_PROG(sb_show_options, struct seq_file *m, struct super_block *sb)
{
	bpf_printk("lsm_hook: fs: sb_show_options\n");
	return 0;
}

SEC("lsm/sb_umount")
int BPF_PROG(sb_umount, struct vfsmount *mnt, int flags)
{
	bpf_printk("lsm_hook: fs: sb_umount\n");
	return 0;
}

SEC("lsm/sb_pivotroot")
int BPF_PROG(sb_pivotroot, const struct path *old_path,
	 const struct path *new_path)
{
	bpf_printk("lsm_hook: fs: sb_pivotroot\n");
	return 0;
}

SEC("lsm/sb_set_mnt_opts")
int BPF_PROG(sb_set_mnt_opts, struct super_block *sb, void *mnt_opts,
	 unsigned long kern_flags, unsigned long *set_kern_flags)
{
	bpf_printk("lsm_hook: fs: sb_set_mnt_opts\n");
	return 0;
}

SEC("lsm/sb_clone_mnt_opts")
int BPF_PROG(sb_clone_mnt_opts, const struct super_block *oldsb,
	 struct super_block *newsb, unsigned long kern_flags,
	 unsigned long *set_kern_flags)
{
	bpf_printk("lsm_hook: fs: sb_clone_mnt_opts\n");
	return 0;
}

SEC("lsm/sb_add_mnt_opt")
int BPF_PROG(sb_add_mnt_opt, const char *option, const char *val,
	 int len, void **mnt_opts)
{
	bpf_printk("lsm_hook: fs: sb_add_mnt_opt\n");
	return 0;
}

// @sb_parse_opts_str


SEC("lsm/move_mount")
int BPF_PROG(move_mount, const struct path *from_path,
	 const struct path *to_path)
{
	bpf_printk("lsm_hook: fs: move_mount\n");
	return 0;
}

//SEC("lsm/dentry_init_security")
//int BPF_PROG(dentry_init_security, struct dentry *dentry,
//	 int mode, const struct qstr *name, void **ctx, u32 *ctxlen)
//{
//	bpf_printk("lsm_hook: fs: dentry_init_security\n");
//	return 0;
//}

SEC("lsm/dentry_create_files_as")
int BPF_PROG(dentry_create_files_as, struct dentry *dentry, int mode,
	 struct qstr *name, const struct cred *old, struct cred *new)
{
	bpf_printk("lsm_hook: fs: dentry_create_files_as\n");
	return 0;
}


// Security hooks for inode operations.

SEC("lsm/inode_alloc_security")
int BPF_PROG(inode_alloc_security, struct inode *inode)
{
	bpf_printk("lsm_hook: inode: inode_alloc_security\n");
	return 0;
}

SEC("lsm/inode_free_security")
void BPF_PROG(inode_free_security, struct inode *inode)
{
	bpf_printk("lsm_hook: inode: inode_free_security\n");
}

SEC("lsm/inode_init_security")
int BPF_PROG(inode_init_security, struct inode *inode,
	 struct inode *dir, const struct qstr *qstr, const char **name,
	 void **value, size_t *len)
{
	bpf_printk("lsm_hook: inode: inode_init_security\n");
	return 0;
}

SEC("lsm/inode_create")
int BPF_PROG(inode_create, struct inode *dir, struct dentry *dentry,
	 umode_t mode)
{
	bpf_printk("lsm_hook: inode: inode_create\n");
	return 0;
}

SEC("lsm/inode_link")
int BPF_PROG(inode_link, struct dentry *old_dentry, struct inode *dir,
	 struct dentry *new_dentry)
{
	bpf_printk("lsm_hook: inode: inode_link\n");
	return 0;
}

SEC("lsm/path_link")
int BPF_PROG(path_link, struct dentry *old_dentry,
	 const struct path *new_dir, struct dentry *new_dentry)
{
	bpf_printk("lsm_hook: inode: path_link\n");
	return 0;
}

SEC("lsm/inode_unlink")
int BPF_PROG(inode_unlink, struct inode *dir, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: inode_unlink\n");
	return 0;
}

SEC("lsm/path_unlink")
int BPF_PROG(path_unlink, const struct path *dir, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: path_unlink\n");
	return 0;
}

SEC("lsm/inode_symlink")
int BPF_PROG(inode_symlink, struct inode *dir, struct dentry *dentry,
	 const char *old_name)
{
	bpf_printk("lsm_hook: inode: inode_symlink\n");
	return 0;
}

SEC("lsm/path_symlink")
int BPF_PROG(path_symlink, const struct path *dir, struct dentry *dentry,
	 const char *old_name)
{
	bpf_printk("lsm_hook: inode: path_symlink\n");
	return 0;
}

SEC("lsm/inode_mkdir")
int BPF_PROG(inode_mkdir, struct inode *dir, struct dentry *dentry,
	 umode_t mode)
{
	bpf_printk("lsm_hook: inode: inode_mkdir\n");
	return 0;
}

SEC("lsm/path_mkdir")
int BPF_PROG(path_mkdir, const struct path *dir, struct dentry *dentry,
	 umode_t mode)
{
	bpf_printk("lsm_hook: inode: path_mkdir\n");
	return 0;
}

SEC("lsm/inode_rmdir")
int BPF_PROG(inode_rmdir, struct inode *dir, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: inode_rmdir\n");
	return 0;
}

SEC("lsm/path_rmdir")
int BPF_PROG(path_rmdir, const struct path *dir, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: path_rmdir\n");
	return 0;
}

SEC("lsm/inode_mknod")
int BPF_PROG(inode_mknod, struct inode *dir, struct dentry *dentry,
	 umode_t mode, dev_t dev)
{
	bpf_printk("lsm_hook: inode: inode_mknod\n");
	return 0;
}

SEC("lsm/inode_rename")
int BPF_PROG(inode_rename, struct inode *old_dir, struct dentry *old_dentry,
	 struct inode *new_dir, struct dentry *new_dentry)
{
	bpf_printk("lsm_hook: inode: inode_rename\n");
	return 0;
}

SEC("lsm/path_rename")
int BPF_PROG(path_rename, const struct path *old_dir,
	 struct dentry *old_dentry, const struct path *new_dir,
	 struct dentry *new_dentry)
{
	bpf_printk("lsm_hook: inode: path_rename\n");
	return 0;
}

SEC("lsm/path_chmod")
int BPF_PROG(path_chmod, const struct path *path, umode_t mode)
{
	bpf_printk("lsm_hook: inode: path_chmod\n");
	return 0;
}

//SEC("lsm/path_chown")
//int BPF_PROG(path_chown, const struct path *path, kuid_t uid, kgid_t gid)
//{
//	bpf_printk("lsm_hook: inode: path_chown\n");
//	return 0;
//}

SEC("lsm/path_chroot")
int BPF_PROG(path_chroot, const struct path *path)
{
	bpf_printk("lsm_hook: inode: path_chroot\n");
	return 0;
}

SEC("lsm/path_notify")
int BPF_PROG(path_notify, const struct path *path, u64 mask,
	 unsigned int obj_type)
{
	bpf_printk("lsm_hook: inode: path_notify\n");
	return 0;
}

SEC("lsm/inode_readlink")
int BPF_PROG(inode_readlink, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: inode_readlink\n");
	return 0;
}

SEC("lsm/inode_follow_link")
int BPF_PROG(inode_follow_link, struct dentry *dentry, struct inode *inode,
	 bool rcu)
{
	bpf_printk("lsm_hook: inode: inode_follow_link\n");
	return 0;
}

SEC("lsm/inode_permission")
int BPF_PROG(inode_permission, struct inode *inode, int mask)
{
	bpf_printk("lsm_hook: inode: inode_permission\n");
	return 0;
}

SEC("lsm/inode_setattr")
int BPF_PROG(inode_setattr, struct dentry *dentry, struct iattr *attr)
{
	bpf_printk("lsm_hook: inode: inode_setattr\n");
	return 0;
}

SEC("lsm/path_truncate")
int BPF_PROG(path_truncate, const struct path *path)
{
	bpf_printk("lsm_hook: inode: path_truncate\n");
	return 0;
}

SEC("lsm/inode_getattr")
int BPF_PROG(inode_getattr, const struct path *path)
{
	bpf_printk("lsm_hook: inode: inode_getattr\n");
	return 0;
}

SEC("lsm/inode_setxattr")
int BPF_PROG(inode_setxattr, struct dentry *dentry, const char *name,
	 const void *value, size_t size, int flags)
{
	bpf_printk("lsm_hook: inode: inode_setxattr\n");
	return 0;
}

SEC("lsm/inode_post_setxattr")
int BPF_PROG(inode_post_setxattr, struct dentry *dentry,
	 const char *name, const void *value, size_t size, int flags)
{
	bpf_printk("lsm_hook: inode: inode_post_setxattr\n");
	return 0;
}

SEC("lsm/inode_getxattr")
int BPF_PROG(inode_getxattr, struct dentry *dentry, const char *name)
{
	bpf_printk("lsm_hook: inode: inode_getxattr\n");
	return 0;
}

SEC("lsm/inode_listxattr")
int BPF_PROG(inode_listxattr, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: inode_listxattr\n");
	return 0;
}

SEC("lsm/inode_removexattr")
int BPF_PROG(inode_removexattr, struct dentry *dentry, const char *name)
{
	bpf_printk("lsm_hook: inode: inode_removexattr\n");
	return 0;
}

SEC("lsm/inode_getsecurity")
int BPF_PROG(inode_getsecurity, struct inode *inode,
	 const char *name, void **buffer, bool alloc)
{
	bpf_printk("lsm_hook: inode: inode_getsecurity\n");
	return 0;
}

SEC("lsm/inode_setsecurity")
int BPF_PROG(inode_setsecurity, struct inode *inode,
	 const char *name, const void *value, size_t size, int flags)
{
	bpf_printk("lsm_hook: inode: inode_setsecurity\n");
	return 0;
}


SEC("lsm/inode_listsecurity")
int BPF_PROG(inode_listsecurity, struct inode *inode, char *buffer,
	 size_t buffer_size)
{
	bpf_printk("lsm_hook: inode: inode_listsecurity\n");
	return 0;
}

SEC("lsm/inode_need_killpriv")
int BPF_PROG(inode_need_killpriv, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: inode_need_killpriv\n");
	return 0;
}

SEC("lsm/inode_killpriv")
int BPF_PROG(inode_killpriv, struct dentry *dentry)
{
	bpf_printk("lsm_hook: inode: inode_killpriv\n");
	return 0;
}

SEC("lsm/inode_getsecid")
void BPF_PROG(inode_getsecid, struct inode *inode, u32 *secid)
{
	bpf_printk("lsm_hook: inode: inode_getsecid\n");
}

SEC("lsm/inode_copy_up")
int BPF_PROG(inode_copy_up, struct dentry *src, struct cred **new)
{
	bpf_printk("lsm_hook: inode: inode_copy_up\n");
	return 0;
}

SEC("lsm/inode_copy_up_xattr")
int BPF_PROG(inode_copy_up_xattr, const char *name)
{
	bpf_printk("lsm_hook: inode: inode_copy_up_xattr\n");
	return 0;
}

SEC("lsm/d_instantiate")
int BPF_PROG(d_instantiate, struct dentry *dentry,
	 struct inode *inode)
{
	bpf_printk("lsm_hook: inode: d_instantiate\n");
	return 0;
}

SEC("lsm/getprocattr")
int BPF_PROG(getprocattr, struct task_struct *p, char *name,
	 char **value)
{
	bpf_printk("lsm_hook: inode: getprocattr\n");
	return 0;
}

SEC("lsm/setprocattr")
int BPF_PROG(setprocattr, const char *name, void *value, size_t size)
{
	bpf_printk("lsm_hook: inode: setprocattr\n");
	return 0;
}


// Security hooks for kernfs node operations

SEC("lsm/kernfs_init_security")
int BPF_PROG(kernfs_init_security, struct kernfs_node *kn_dir,
	 struct kernfs_node *kn)
{
	bpf_printk("lsm_hook: inode: kernfs_init_security\n");
	return 0;
}


// Security hooks for file operations

SEC("lsm/file_permission")
int BPF_PROG(file_permission, struct file *file, int mask)
{
	bpf_printk("lsm_hook: inode: file_permission\n");
	return 0;
}

SEC("lsm/file_alloc_security")
int BPF_PROG(file_alloc_security, struct file *file)
{
	bpf_printk("lsm_hook: inode: file_alloc_security\n");
	return 0;
}

SEC("lsm/file_alloc_security")
void BPF_PROG(file_free_security, struct file *file)
{
	bpf_printk("lsm_hook: inode: file_free_security\n");
}

SEC("lsm/file_ioctl")
int BPF_PROG(file_ioctl, struct file *file, unsigned int cmd,
	 unsigned long arg)
{
	bpf_printk("lsm_hook: inode: file_ioctl\n");
	return 0;
}

SEC("lsm/mmap_addr")
int BPF_PROG(mmap_addr, unsigned long addr)
{
	bpf_printk("lsm_hook: inode: mmap_addr\n");
	return 0;
}

SEC("lsm/mmap_file")
int BPF_PROG(mmap_file, struct file *file, unsigned long reqprot,
	 unsigned long prot, unsigned long flags)
{
	bpf_printk("lsm_hook: inode: mmap_file\n");
	return 0;
}

SEC("lsm/file_mprotect")
int BPF_PROG(file_mprotect, struct vm_area_struct *vma,
	 unsigned long reqprot, unsigned long prot)
{
	bpf_printk("lsm_hook: inode: file_mprotect\n");
	return 0;
}

SEC("lsm/file_lock")
int BPF_PROG(file_lock, struct file *file, unsigned int cmd)
{
	bpf_printk("lsm_hook: inode: file_mprotect\n");
	return 0;
}

SEC("lsm/file_fcntl")
int BPF_PROG(file_fcntl, struct file *file, unsigned int cmd,
	 unsigned long arg)
{
	bpf_printk("lsm_hook: inode: file_fcntl\n");
	return 0;
}









char _license[] SEC("license") = "GPL";


// Not implemented:
// sb_copy_data
// sb_parse_opts_str






//SEC("lsm/bprm_committed_creds")
//void BPF_PROG(bprm_committed_creds, struct linux_binprm *bprm)
//{
//	bpf_printk("lsm_hook: bprm_committed_creds\n");
//	long pid_tgid;
//	struct process_info *process;
//	struct task_struct *current_task;
//
//	// Reserve space on the ringbuffer for the sample
//	process = bpf_ringbuf_reserve(&ringbuf, sizeof(*process), ringbuffer_flags);
//	if (!process)
//		return;
//
//	// Get information about the current process
//	pid_tgid = bpf_get_current_pid_tgid();
//	process->pid = pid_tgid;
//	process->tgid = pid_tgid >> 32;
//
//	// Get the parent pid
//	current_task = (struct task_struct *)bpf_get_current_task();
//	process->ppid = BPF_CORE_READ(current_task, real_parent, pid);
//
//	// Get the executable name
//	bpf_get_current_comm(&process->name, sizeof(process->name));
//
//	bpf_ringbuf_submit(process, ringbuffer_flags);
//}



