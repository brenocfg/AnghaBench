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
struct thread {int dummy; } ;
struct synclist {int dummy; } ;
struct mount {int dummy; } ;
struct bufobj {int bo_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int BO_ONWORKLST ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 struct bufobj* LIST_FIRST (struct synclist*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  MNT_LAZY ; 
 scalar_t__ VI_TRYLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VOP_FSYNC (struct vnode*,int /*<<< orphan*/ ,struct thread*) ; 
 scalar_t__ VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_NOWAIT ; 
 struct vnode* bo2vnode (struct bufobj*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  syncdelay ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vholdl (struct vnode*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 scalar_t__ vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_syncer_add_to_worklist (struct bufobj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sync_vnode(struct synclist *slp, struct bufobj **bo, struct thread *td)
{
	struct vnode *vp;
	struct mount *mp;

	*bo = LIST_FIRST(slp);
	if (*bo == NULL)
		return (0);
	vp = bo2vnode(*bo);
	if (VOP_ISLOCKED(vp) != 0 || VI_TRYLOCK(vp) == 0)
		return (1);
	/*
	 * We use vhold in case the vnode does not
	 * successfully sync.  vhold prevents the vnode from
	 * going away when we unlock the sync_mtx so that
	 * we can acquire the vnode interlock.
	 */
	vholdl(vp);
	mtx_unlock(&sync_mtx);
	VI_UNLOCK(vp);
	if (vn_start_write(vp, &mp, V_NOWAIT) != 0) {
		vdrop(vp);
		mtx_lock(&sync_mtx);
		return (*bo == LIST_FIRST(slp));
	}
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	(void) VOP_FSYNC(vp, MNT_LAZY, td);
	VOP_UNLOCK(vp, 0);
	vn_finished_write(mp);
	BO_LOCK(*bo);
	if (((*bo)->bo_flag & BO_ONWORKLST) != 0) {
		/*
		 * Put us back on the worklist.  The worklist
		 * routine will remove us from our current
		 * position and then add us back in at a later
		 * position.
		 */
		vn_syncer_add_to_worklist(*bo, syncdelay);
	}
	BO_UNLOCK(*bo);
	vdrop(vp);
	mtx_lock(&sync_mtx);
	return (0);
}