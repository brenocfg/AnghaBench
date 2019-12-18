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
struct vnode {int /*<<< orphan*/  v_vflag; } ;
struct mount {int dummy; } ;
struct devfs_mount {int /*<<< orphan*/  dm_rootdir; int /*<<< orphan*/  dm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 struct devfs_mount* VFSTODEVFS (struct mount*) ; 
 int /*<<< orphan*/  VV_ROOT ; 
 int devfs_allocv (int /*<<< orphan*/ ,struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devfs_root(struct mount *mp, int flags, struct vnode **vpp)
{
	int error;
	struct vnode *vp;
	struct devfs_mount *dmp;

	dmp = VFSTODEVFS(mp);
	sx_xlock(&dmp->dm_lock);
	error = devfs_allocv(dmp->dm_rootdir, mp, LK_EXCLUSIVE, &vp);
	if (error)
		return (error);
	vp->v_vflag |= VV_ROOT;
	*vpp = vp;
	return (0);
}