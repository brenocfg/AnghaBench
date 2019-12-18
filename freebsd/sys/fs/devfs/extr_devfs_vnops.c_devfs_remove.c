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
struct vop_remove_args {struct vnode* a_dvp; struct vnode* a_vp; } ;
struct vnode {struct devfs_dirent* v_data; int /*<<< orphan*/  v_mount; } ;
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int /*<<< orphan*/  de_flags; TYPE_1__* de_dirent; int /*<<< orphan*/  de_dlist; int /*<<< orphan*/ * de_cdp; } ;
struct TYPE_2__ {scalar_t__ d_type; int /*<<< orphan*/  d_namlen; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  DE_COVERED ; 
 int /*<<< orphan*/  DE_WHITEOUT ; 
 scalar_t__ DT_LNK ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 struct devfs_mount* VFSTODEVFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de_list ; 
 int /*<<< orphan*/  devfs_delete (struct devfs_mount*,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 struct devfs_dirent* devfs_find (struct devfs_dirent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
devfs_remove(struct vop_remove_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct vnode *vp = ap->a_vp;
	struct devfs_dirent *dd;
	struct devfs_dirent *de, *de_covered;
	struct devfs_mount *dmp = VFSTODEVFS(vp->v_mount);

	ASSERT_VOP_ELOCKED(dvp, "devfs_remove");
	ASSERT_VOP_ELOCKED(vp, "devfs_remove");

	sx_xlock(&dmp->dm_lock);
	dd = ap->a_dvp->v_data;
	de = vp->v_data;
	if (de->de_cdp == NULL) {
		TAILQ_REMOVE(&dd->de_dlist, de, de_list);
		if (de->de_dirent->d_type == DT_LNK) {
			de_covered = devfs_find(dd, de->de_dirent->d_name,
			    de->de_dirent->d_namlen, 0);
			if (de_covered != NULL)
				de_covered->de_flags &= ~DE_COVERED;
		}
		/* We need to unlock dvp because devfs_delete() may lock it. */
		VOP_UNLOCK(vp, 0);
		if (dvp != vp)
			VOP_UNLOCK(dvp, 0);
		devfs_delete(dmp, de, 0);
		sx_xunlock(&dmp->dm_lock);
		if (dvp != vp)
			vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY);
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	} else {
		de->de_flags |= DE_WHITEOUT;
		sx_xunlock(&dmp->dm_lock);
	}
	return (0);
}