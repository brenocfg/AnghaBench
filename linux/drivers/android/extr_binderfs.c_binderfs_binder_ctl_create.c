#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {struct binderfs_info* s_fs_info; struct dentry* s_root; } ;
struct inode {struct binder_device* i_private; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;
struct binderfs_info {struct dentry* control_dentry; int /*<<< orphan*/  root_gid; int /*<<< orphan*/  root_uid; int /*<<< orphan*/ * ipc_ns; } ;
struct TYPE_2__ {int minor; } ;
struct binder_device {TYPE_1__ miscdev; struct inode* binderfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDERFS_MAX_MINOR ; 
 int /*<<< orphan*/  BINDERFS_MAX_MINOR_CAPPED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SECOND_INODE ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  binder_ctl_fops ; 
 int /*<<< orphan*/  binderfs_dev ; 
 int /*<<< orphan*/  binderfs_minors ; 
 int /*<<< orphan*/  binderfs_minors_mutex ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char*) ; 
 int ida_alloc_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_ipc_ns ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct binder_device*) ; 
 struct binder_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 

__attribute__((used)) static int binderfs_binder_ctl_create(struct super_block *sb)
{
	int minor, ret;
	struct dentry *dentry;
	struct binder_device *device;
	struct inode *inode = NULL;
	struct dentry *root = sb->s_root;
	struct binderfs_info *info = sb->s_fs_info;
#if defined(CONFIG_IPC_NS)
	bool use_reserve = (info->ipc_ns == &init_ipc_ns);
#else
	bool use_reserve = true;
#endif

	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (!device)
		return -ENOMEM;

	/* If we have already created a binder-control node, return. */
	if (info->control_dentry) {
		ret = 0;
		goto out;
	}

	ret = -ENOMEM;
	inode = new_inode(sb);
	if (!inode)
		goto out;

	/* Reserve a new minor number for the new device. */
	mutex_lock(&binderfs_minors_mutex);
	minor = ida_alloc_max(&binderfs_minors,
			      use_reserve ? BINDERFS_MAX_MINOR :
					    BINDERFS_MAX_MINOR_CAPPED,
			      GFP_KERNEL);
	mutex_unlock(&binderfs_minors_mutex);
	if (minor < 0) {
		ret = minor;
		goto out;
	}

	inode->i_ino = SECOND_INODE;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	init_special_inode(inode, S_IFCHR | 0600,
			   MKDEV(MAJOR(binderfs_dev), minor));
	inode->i_fop = &binder_ctl_fops;
	inode->i_uid = info->root_uid;
	inode->i_gid = info->root_gid;

	device->binderfs_inode = inode;
	device->miscdev.minor = minor;

	dentry = d_alloc_name(root, "binder-control");
	if (!dentry)
		goto out;

	inode->i_private = device;
	info->control_dentry = dentry;
	d_add(dentry, inode);

	return 0;

out:
	kfree(device);
	iput(inode);

	return ret;
}