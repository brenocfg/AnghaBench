#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {int v_iflag; struct mount* v_mount; } ;
struct mount {int dummy; } ;
struct TYPE_3__ {struct vnode* p_textvp; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  MBF_NOWAIT ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mount*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* curproc ; 
 TYPE_1__* initproc ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mountcheckdirs (struct vnode*,struct vnode*) ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  mountlist_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct mount* rootdevmp ; 
 struct vnode* rootvnode ; 
 int vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_mountroot () ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vfs_rel (struct mount*) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vfs_unmountall () ; 
 int vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
kern_reroot(void)
{
	struct vnode *oldrootvnode, *vp;
	struct mount *mp, *devmp;
	int error;

	if (curproc != initproc)
		return (EPERM);

	/*
	 * Mark the filesystem containing currently-running executable
	 * (the temporary copy of init(8)) busy.
	 */
	vp = curproc->p_textvp;
	error = vn_lock(vp, LK_SHARED);
	if (error != 0)
		return (error);
	mp = vp->v_mount;
	error = vfs_busy(mp, MBF_NOWAIT);
	if (error != 0) {
		vfs_ref(mp);
		VOP_UNLOCK(vp, 0);
		error = vfs_busy(mp, 0);
		vn_lock(vp, LK_SHARED | LK_RETRY);
		vfs_rel(mp);
		if (error != 0) {
			VOP_UNLOCK(vp, 0);
			return (ENOENT);
		}
		if (vp->v_iflag & VI_DOOMED) {
			VOP_UNLOCK(vp, 0);
			vfs_unbusy(mp);
			return (ENOENT);
		}
	}
	VOP_UNLOCK(vp, 0);

	/*
	 * Remove the filesystem containing currently-running executable
	 * from the mount list, to prevent it from being unmounted
	 * by vfs_unmountall(), and to avoid confusing vfs_mountroot().
	 *
	 * Also preserve /dev - forcibly unmounting it could cause driver
	 * reinitialization.
	 */

	vfs_ref(rootdevmp);
	devmp = rootdevmp;
	rootdevmp = NULL;

	mtx_lock(&mountlist_mtx);
	TAILQ_REMOVE(&mountlist, mp, mnt_list);
	TAILQ_REMOVE(&mountlist, devmp, mnt_list);
	mtx_unlock(&mountlist_mtx);

	oldrootvnode = rootvnode;

	/*
	 * Unmount everything except for the two filesystems preserved above.
	 */
	vfs_unmountall();

	/*
	 * Add /dev back; vfs_mountroot() will move it into its new place.
	 */
	mtx_lock(&mountlist_mtx);
	TAILQ_INSERT_HEAD(&mountlist, devmp, mnt_list);
	mtx_unlock(&mountlist_mtx);
	rootdevmp = devmp;
	vfs_rel(rootdevmp);

	/*
	 * Mount the new rootfs.
	 */
	vfs_mountroot();

	/*
	 * Update all references to the old rootvnode.
	 */
	mountcheckdirs(oldrootvnode, rootvnode);

	/*
	 * Add the temporary filesystem back and unbusy it.
	 */
	mtx_lock(&mountlist_mtx);
	TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);
	mtx_unlock(&mountlist_mtx);
	vfs_unbusy(mp);

	return (0);
}