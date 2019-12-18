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
struct vop_fsync_args {scalar_t__ a_waitfor; struct vnode* a_vp; } ;
struct bufobj {int dummy; } ;
struct vnode {struct bufobj v_bufobj; struct mount* v_mount; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int /*<<< orphan*/  MBF_NOWAIT ; 
 scalar_t__ MNT_LAZY ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int /*<<< orphan*/  TDP_SYNCIO ; 
 int VFS_SYNC (struct mount*,scalar_t__) ; 
 int /*<<< orphan*/  V_NOWAIT ; 
 int /*<<< orphan*/  curthread_pflags_restore (int) ; 
 int curthread_pflags_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syncdelay ; 
 scalar_t__ vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_msync (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 scalar_t__ vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_syncer_add_to_worklist (struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnlru_return_batch (struct mount*) ; 

__attribute__((used)) static int
sync_fsync(struct vop_fsync_args *ap)
{
	struct vnode *syncvp = ap->a_vp;
	struct mount *mp = syncvp->v_mount;
	int error, save;
	struct bufobj *bo;

	/*
	 * We only need to do something if this is a lazy evaluation.
	 */
	if (ap->a_waitfor != MNT_LAZY)
		return (0);

	/*
	 * Move ourselves to the back of the sync list.
	 */
	bo = &syncvp->v_bufobj;
	BO_LOCK(bo);
	vn_syncer_add_to_worklist(bo, syncdelay);
	BO_UNLOCK(bo);

	/*
	 * Walk the list of vnodes pushing all that are dirty and
	 * not already on the sync list.
	 */
	if (vfs_busy(mp, MBF_NOWAIT) != 0)
		return (0);
	if (vn_start_write(NULL, &mp, V_NOWAIT) != 0) {
		vfs_unbusy(mp);
		return (0);
	}
	save = curthread_pflags_set(TDP_SYNCIO);
	/*
	 * The filesystem at hand may be idle with free vnodes stored in the
	 * batch.  Return them instead of letting them stay there indefinitely.
	 */
	vnlru_return_batch(mp);
	vfs_msync(mp, MNT_NOWAIT);
	error = VFS_SYNC(mp, MNT_LAZY);
	curthread_pflags_restore(save);
	vn_finished_write(mp);
	vfs_unbusy(mp);
	return (error);
}