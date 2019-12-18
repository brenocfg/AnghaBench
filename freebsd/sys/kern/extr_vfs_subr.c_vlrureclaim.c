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
struct vnode {scalar_t__ v_type; int v_iflag; TYPE_1__* v_object; int /*<<< orphan*/  v_cache_src; scalar_t__ v_usecount; } ;
struct mount {int mnt_nvnodelistsize; int /*<<< orphan*/  mnt_nvnodelist; } ;
typedef  int int64_t ;
struct TYPE_2__ {int resident_page_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int LK_EXCLUSIVE ; 
 int LK_INTERLOCK ; 
 int LK_NOWAIT ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  PRI_USER ; 
 struct vnode* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 struct vnode* TAILQ_NEXT (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int VI_FREE ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_TRYLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 scalar_t__ VMARKER ; 
 scalar_t__ VOP_LOCK (struct vnode*,int) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  desiredvnodes ; 
 scalar_t__ gapvnodes ; 
 int imax (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recycles_count ; 
 int /*<<< orphan*/  should_yield () ; 
 int /*<<< orphan*/  v_nmntvnodes ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vdropl (struct vnode*) ; 
 int /*<<< orphan*/  vgonel (struct vnode*) ; 
 int /*<<< orphan*/  vholdl (struct vnode*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_start_write (int /*<<< orphan*/ *,struct mount**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vlrureclaim(struct mount *mp, bool reclaim_nc_src, int trigger)
{
	struct vnode *vp;
	int count, done, target;

	done = 0;
	vn_start_write(NULL, &mp, V_WAIT);
	MNT_ILOCK(mp);
	count = mp->mnt_nvnodelistsize;
	target = count * (int64_t)gapvnodes / imax(desiredvnodes, 1);
	target = target / 10 + 1;
	while (count != 0 && done < target) {
		vp = TAILQ_FIRST(&mp->mnt_nvnodelist);
		while (vp != NULL && vp->v_type == VMARKER)
			vp = TAILQ_NEXT(vp, v_nmntvnodes);
		if (vp == NULL)
			break;
		/*
		 * XXX LRU is completely broken for non-free vnodes.  First
		 * by calling here in mountpoint order, then by moving
		 * unselected vnodes to the end here, and most grossly by
		 * removing the vlruvp() function that was supposed to
		 * maintain the order.  (This function was born broken
		 * since syncer problems prevented it doing anything.)  The
		 * order is closer to LRC (C = Created).
		 *
		 * LRU reclaiming of vnodes seems to have last worked in
		 * FreeBSD-3 where LRU wasn't mentioned under any spelling.
		 * Then there was no hold count, and inactive vnodes were
		 * simply put on the free list in LRU order.  The separate
		 * lists also break LRU.  We prefer to reclaim from the
		 * free list for technical reasons.  This tends to thrash
		 * the free list to keep very unrecently used held vnodes.
		 * The problem is mitigated by keeping the free list large.
		 */
		TAILQ_REMOVE(&mp->mnt_nvnodelist, vp, v_nmntvnodes);
		TAILQ_INSERT_TAIL(&mp->mnt_nvnodelist, vp, v_nmntvnodes);
		--count;
		if (!VI_TRYLOCK(vp))
			goto next_iter;
		/*
		 * If it's been deconstructed already, it's still
		 * referenced, or it exceeds the trigger, skip it.
		 * Also skip free vnodes.  We are trying to make space
		 * to expand the free list, not reduce it.
		 */
		if (vp->v_usecount ||
		    (!reclaim_nc_src && !LIST_EMPTY(&vp->v_cache_src)) ||
		    ((vp->v_iflag & VI_FREE) != 0) ||
		    (vp->v_iflag & VI_DOOMED) != 0 || (vp->v_object != NULL &&
		    vp->v_object->resident_page_count > trigger)) {
			VI_UNLOCK(vp);
			goto next_iter;
		}
		MNT_IUNLOCK(mp);
		vholdl(vp);
		if (VOP_LOCK(vp, LK_INTERLOCK|LK_EXCLUSIVE|LK_NOWAIT)) {
			vdrop(vp);
			goto next_iter_mntunlocked;
		}
		VI_LOCK(vp);
		/*
		 * v_usecount may have been bumped after VOP_LOCK() dropped
		 * the vnode interlock and before it was locked again.
		 *
		 * It is not necessary to recheck VI_DOOMED because it can
		 * only be set by another thread that holds both the vnode
		 * lock and vnode interlock.  If another thread has the
		 * vnode lock before we get to VOP_LOCK() and obtains the
		 * vnode interlock after VOP_LOCK() drops the vnode
		 * interlock, the other thread will be unable to drop the
		 * vnode lock before our VOP_LOCK() call fails.
		 */
		if (vp->v_usecount ||
		    (!reclaim_nc_src && !LIST_EMPTY(&vp->v_cache_src)) ||
		    (vp->v_iflag & VI_FREE) != 0 ||
		    (vp->v_object != NULL &&
		    vp->v_object->resident_page_count > trigger)) {
			VOP_UNLOCK(vp, 0);
			vdropl(vp);
			goto next_iter_mntunlocked;
		}
		KASSERT((vp->v_iflag & VI_DOOMED) == 0,
		    ("VI_DOOMED unexpectedly detected in vlrureclaim()"));
		counter_u64_add(recycles_count, 1);
		vgonel(vp);
		VOP_UNLOCK(vp, 0);
		vdropl(vp);
		done++;
next_iter_mntunlocked:
		if (!should_yield())
			goto relock_mnt;
		goto yield;
next_iter:
		if (!should_yield())
			continue;
		MNT_IUNLOCK(mp);
yield:
		kern_yield(PRI_USER);
relock_mnt:
		MNT_ILOCK(mp);
	}
	MNT_IUNLOCK(mp);
	vn_finished_write(mp);
	return done;
}