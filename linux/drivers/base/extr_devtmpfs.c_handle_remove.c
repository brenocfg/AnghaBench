#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct kstat {int mode; } ;
struct iattr {int ia_mode; int ia_valid; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct device {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  AT_STATX_SYNC_AS_STAT ; 
 int ENOENT ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int STATX_MODE ; 
 int STATX_TYPE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  delete_path (char const*) ; 
 scalar_t__ dev_mynode (struct device*,int /*<<< orphan*/ ,struct kstat*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* kern_path_locked (char const*,struct path*) ; 
 int /*<<< orphan*/  notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int vfs_getattr (struct path*,struct kstat*,int,int /*<<< orphan*/ ) ; 
 int vfs_unlink (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_remove(const char *nodename, struct device *dev)
{
	struct path parent;
	struct dentry *dentry;
	int deleted = 0;
	int err;

	dentry = kern_path_locked(nodename, &parent);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	if (d_really_is_positive(dentry)) {
		struct kstat stat;
		struct path p = {.mnt = parent.mnt, .dentry = dentry};
		err = vfs_getattr(&p, &stat, STATX_TYPE | STATX_MODE,
				  AT_STATX_SYNC_AS_STAT);
		if (!err && dev_mynode(dev, d_inode(dentry), &stat)) {
			struct iattr newattrs;
			/*
			 * before unlinking this node, reset permissions
			 * of possible references like hardlinks
			 */
			newattrs.ia_uid = GLOBAL_ROOT_UID;
			newattrs.ia_gid = GLOBAL_ROOT_GID;
			newattrs.ia_mode = stat.mode & ~0777;
			newattrs.ia_valid =
				ATTR_UID|ATTR_GID|ATTR_MODE;
			inode_lock(d_inode(dentry));
			notify_change(dentry, &newattrs, NULL);
			inode_unlock(d_inode(dentry));
			err = vfs_unlink(d_inode(parent.dentry), dentry, NULL);
			if (!err || err == -ENOENT)
				deleted = 1;
		}
	} else {
		err = -ENOENT;
	}
	dput(dentry);
	inode_unlock(d_inode(parent.dentry));

	path_put(&parent);
	if (deleted && strchr(nodename, '/'))
		delete_path(nodename);
	return err;
}