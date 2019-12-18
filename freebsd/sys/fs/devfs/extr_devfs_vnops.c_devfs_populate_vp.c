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
struct vnode {int v_iflag; struct devfs_dirent* v_data; int /*<<< orphan*/  v_mount; } ;
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int de_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 scalar_t__ DEVFS_DMP_DROP (struct devfs_mount*) ; 
 int /*<<< orphan*/  DEVFS_DMP_HOLD (struct devfs_mount*) ; 
 int DE_DOOMED ; 
 int ERESTART ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LK_RETRY ; 
 struct devfs_mount* VFSTODEVFS (int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_populate (struct devfs_mount*) ; 
 int /*<<< orphan*/  devfs_unmount_final (struct devfs_mount*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
devfs_populate_vp(struct vnode *vp)
{
	struct devfs_dirent *de;
	struct devfs_mount *dmp;
	int locked;

	ASSERT_VOP_LOCKED(vp, "devfs_populate_vp");

	dmp = VFSTODEVFS(vp->v_mount);
	locked = VOP_ISLOCKED(vp);

	sx_xlock(&dmp->dm_lock);
	DEVFS_DMP_HOLD(dmp);

	/* Can't call devfs_populate() with the vnode lock held. */
	VOP_UNLOCK(vp, 0);
	devfs_populate(dmp);

	sx_xunlock(&dmp->dm_lock);
	vn_lock(vp, locked | LK_RETRY);
	sx_xlock(&dmp->dm_lock);
	if (DEVFS_DMP_DROP(dmp)) {
		sx_xunlock(&dmp->dm_lock);
		devfs_unmount_final(dmp);
		return (ERESTART);
	}
	if ((vp->v_iflag & VI_DOOMED) != 0) {
		sx_xunlock(&dmp->dm_lock);
		return (ERESTART);
	}
	de = vp->v_data;
	KASSERT(de != NULL,
	    ("devfs_populate_vp: vp->v_data == NULL but vnode not doomed"));
	if ((de->de_flags & DE_DOOMED) != 0) {
		sx_xunlock(&dmp->dm_lock);
		return (ERESTART);
	}

	return (0);
}