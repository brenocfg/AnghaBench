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
struct vop_ioctl_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_data; int /*<<< orphan*/  a_command; struct vnode* a_vp; } ;
struct vnode {int v_iflag; int /*<<< orphan*/  v_mount; } ;
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;

/* Variables and functions */
 scalar_t__ DEVFS_DMP_DROP (struct devfs_mount*) ; 
 int /*<<< orphan*/  DEVFS_DMP_HOLD (struct devfs_mount*) ; 
 int EBADF ; 
 int ENOENT ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 struct devfs_mount* VFSTODEVFS (int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_populate (struct devfs_mount*) ; 
 int devfs_rules_ioctl (struct devfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_unmount_final (struct devfs_mount*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
devfs_rioctl(struct vop_ioctl_args *ap)
{
	struct vnode *vp;
	struct devfs_mount *dmp;
	int error;

	vp = ap->a_vp;
	vn_lock(vp, LK_SHARED | LK_RETRY);
	if (vp->v_iflag & VI_DOOMED) {
		VOP_UNLOCK(vp, 0);
		return (EBADF);
	}
	dmp = VFSTODEVFS(vp->v_mount);
	sx_xlock(&dmp->dm_lock);
	VOP_UNLOCK(vp, 0);
	DEVFS_DMP_HOLD(dmp);
	devfs_populate(dmp);
	if (DEVFS_DMP_DROP(dmp)) {
		sx_xunlock(&dmp->dm_lock);
		devfs_unmount_final(dmp);
		return (ENOENT);
	}
	error = devfs_rules_ioctl(dmp, ap->a_command, ap->a_data, ap->a_td);
	sx_xunlock(&dmp->dm_lock);
	return (error);
}