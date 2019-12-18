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
struct vnode {int dummy; } ;
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int de_flags; scalar_t__ de_inode; int /*<<< orphan*/ * de_symlink; struct vnode* de_vnode; } ;

/* Variables and functions */
 int DEVFS_DEL_NORECURSE ; 
 int DEVFS_DEL_VNLOCKED ; 
 scalar_t__ DEVFS_DE_DROP (struct devfs_dirent*) ; 
 int /*<<< orphan*/  DEVFS_DE_HOLD (struct devfs_dirent*) ; 
 scalar_t__ DEVFS_ROOTINO ; 
 int DE_DOOMED ; 
 int DE_USER ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_INTERLOCK ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  M_DEVFS ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_de_interlock ; 
 int /*<<< orphan*/  devfs_dir_unref_de (struct devfs_mount*,struct devfs_dirent*) ; 
 int /*<<< orphan*/  devfs_dirent_free (struct devfs_dirent*) ; 
 int /*<<< orphan*/  devfs_free_cdp_inode (scalar_t__) ; 
 struct devfs_dirent* devfs_parent_dirent (struct devfs_dirent*) ; 
 int /*<<< orphan*/  devfs_rmdir_empty (struct devfs_mount*,struct devfs_dirent*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_devfs_destroy (struct devfs_dirent*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vholdl (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

void
devfs_delete(struct devfs_mount *dm, struct devfs_dirent *de, int flags)
{
	struct devfs_dirent *dd;
	struct vnode *vp;

	KASSERT((de->de_flags & DE_DOOMED) == 0,
		("devfs_delete doomed dirent"));
	de->de_flags |= DE_DOOMED;

	if ((flags & DEVFS_DEL_NORECURSE) == 0) {
		dd = devfs_parent_dirent(de);
		if (dd != NULL)
			DEVFS_DE_HOLD(dd);
		if (de->de_flags & DE_USER) {
			KASSERT(dd != NULL, ("devfs_delete: NULL dd"));
			devfs_dir_unref_de(dm, dd);
		}
	} else
		dd = NULL;

	mtx_lock(&devfs_de_interlock);
	vp = de->de_vnode;
	if (vp != NULL) {
		VI_LOCK(vp);
		mtx_unlock(&devfs_de_interlock);
		vholdl(vp);
		sx_unlock(&dm->dm_lock);
		if ((flags & DEVFS_DEL_VNLOCKED) == 0)
			vn_lock(vp, LK_EXCLUSIVE | LK_INTERLOCK | LK_RETRY);
		else
			VI_UNLOCK(vp);
		vgone(vp);
		if ((flags & DEVFS_DEL_VNLOCKED) == 0)
			VOP_UNLOCK(vp, 0);
		vdrop(vp);
		sx_xlock(&dm->dm_lock);
	} else
		mtx_unlock(&devfs_de_interlock);
	if (de->de_symlink) {
		free(de->de_symlink, M_DEVFS);
		de->de_symlink = NULL;
	}
#ifdef MAC
	mac_devfs_destroy(de);
#endif
	if (de->de_inode > DEVFS_ROOTINO) {
		devfs_free_cdp_inode(de->de_inode);
		de->de_inode = 0;
	}
	if (DEVFS_DE_DROP(de))
		devfs_dirent_free(de);

	if (dd != NULL) {
		if (DEVFS_DE_DROP(dd))
			devfs_dirent_free(dd);
		else
			devfs_rmdir_empty(dm, dd);
	}
}