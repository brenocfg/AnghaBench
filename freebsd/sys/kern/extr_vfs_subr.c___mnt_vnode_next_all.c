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
struct vnode {scalar_t__ v_type; int v_iflag; struct mount* v_mount; } ;
struct mount {int /*<<< orphan*/  mnt_nvnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_MTX (struct mount*) ; 
 int /*<<< orphan*/  PRI_USER ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct vnode*,struct vnode*,int /*<<< orphan*/ ) ; 
 struct vnode* TAILQ_NEXT (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 scalar_t__ VMARKER ; 
 int /*<<< orphan*/  __mnt_vnode_markerfree_all (struct vnode**,struct mount*) ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ should_yield () ; 
 int /*<<< orphan*/  v_nmntvnodes ; 

struct vnode *
__mnt_vnode_next_all(struct vnode **mvp, struct mount *mp)
{
	struct vnode *vp;

	if (should_yield())
		kern_yield(PRI_USER);
	MNT_ILOCK(mp);
	KASSERT((*mvp)->v_mount == mp, ("marker vnode mount list mismatch"));
	for (vp = TAILQ_NEXT(*mvp, v_nmntvnodes); vp != NULL;
	    vp = TAILQ_NEXT(vp, v_nmntvnodes)) {
		/* Allow a racy peek at VI_DOOMED to save a lock acquisition. */
		if (vp->v_type == VMARKER || (vp->v_iflag & VI_DOOMED) != 0)
			continue;
		VI_LOCK(vp);
		if ((vp->v_iflag & VI_DOOMED) != 0) {
			VI_UNLOCK(vp);
			continue;
		}
		break;
	}
	if (vp == NULL) {
		__mnt_vnode_markerfree_all(mvp, mp);
		/* MNT_IUNLOCK(mp); -- done in above function */
		mtx_assert(MNT_MTX(mp), MA_NOTOWNED);
		return (NULL);
	}
	TAILQ_REMOVE(&mp->mnt_nvnodelist, *mvp, v_nmntvnodes);
	TAILQ_INSERT_AFTER(&mp->mnt_nvnodelist, vp, *mvp, v_nmntvnodes);
	MNT_IUNLOCK(mp);
	return (vp);
}