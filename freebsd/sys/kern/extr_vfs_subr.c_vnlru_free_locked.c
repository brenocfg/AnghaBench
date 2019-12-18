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
struct vnode {int v_iflag; scalar_t__ v_holdcnt; struct mount* v_mount; int /*<<< orphan*/ * v_op; } ;
struct vfsops {int dummy; } ;
struct mount {struct vfsops* mnt_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct vnode* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_ACTIVE ; 
 int VI_FREE ; 
 int /*<<< orphan*/  VI_TRYLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VNASSERT (int,struct vnode*,char*) ; 
 int /*<<< orphan*/  VNODE_REFCOUNT_FENCE_REL () ; 
 int /*<<< orphan*/  freevnodes ; 
 int max_vnlru_free ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_acquire (scalar_t__*) ; 
 int /*<<< orphan*/  v_actfreelist ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vnlru_return_batches (struct vfsops*) ; 
 int /*<<< orphan*/  vnode_free_list ; 
 int /*<<< orphan*/  vnode_free_list_mtx ; 
 int /*<<< orphan*/  vtryrecycle (struct vnode*) ; 

__attribute__((used)) static void
vnlru_free_locked(int count, struct vfsops *mnt_op)
{
	struct vnode *vp;
	struct mount *mp;
	bool tried_batches;

	tried_batches = false;
	mtx_assert(&vnode_free_list_mtx, MA_OWNED);
	if (count > max_vnlru_free)
		count = max_vnlru_free;
	for (; count > 0; count--) {
		vp = TAILQ_FIRST(&vnode_free_list);
		/*
		 * The list can be modified while the free_list_mtx
		 * has been dropped and vp could be NULL here.
		 */
		if (vp == NULL) {
			if (tried_batches)
				break;
			mtx_unlock(&vnode_free_list_mtx);
			vnlru_return_batches(mnt_op);
			tried_batches = true;
			mtx_lock(&vnode_free_list_mtx);
			continue;
		}

		VNASSERT(vp->v_op != NULL, vp,
		    ("vnlru_free: vnode already reclaimed."));
		KASSERT((vp->v_iflag & VI_FREE) != 0,
		    ("Removing vnode not on freelist"));
		KASSERT((vp->v_iflag & VI_ACTIVE) == 0,
		    ("Mangling active vnode"));
		TAILQ_REMOVE(&vnode_free_list, vp, v_actfreelist);

		/*
		 * Don't recycle if our vnode is from different type
		 * of mount point.  Note that mp is type-safe, the
		 * check does not reach unmapped address even if
		 * vnode is reclaimed.
		 * Don't recycle if we can't get the interlock without
		 * blocking.
		 */
		if ((mnt_op != NULL && (mp = vp->v_mount) != NULL &&
		    mp->mnt_op != mnt_op) || !VI_TRYLOCK(vp)) {
			TAILQ_INSERT_TAIL(&vnode_free_list, vp, v_actfreelist);
			continue;
		}
		VNASSERT((vp->v_iflag & VI_FREE) != 0 && vp->v_holdcnt == 0,
		    vp, ("vp inconsistent on freelist"));

		/*
		 * The clear of VI_FREE prevents activation of the
		 * vnode.  There is no sense in putting the vnode on
		 * the mount point active list, only to remove it
		 * later during recycling.  Inline the relevant part
		 * of vholdl(), to avoid triggering assertions or
		 * activating.
		 */
		freevnodes--;
		vp->v_iflag &= ~VI_FREE;
		VNODE_REFCOUNT_FENCE_REL();
		refcount_acquire(&vp->v_holdcnt);

		mtx_unlock(&vnode_free_list_mtx);
		VI_UNLOCK(vp);
		vtryrecycle(vp);
		/*
		 * If the recycled succeeded this vdrop will actually free
		 * the vnode.  If not it will simply place it back on
		 * the free list.
		 */
		vdrop(vp);
		mtx_lock(&vnode_free_list_mtx);
	}
}