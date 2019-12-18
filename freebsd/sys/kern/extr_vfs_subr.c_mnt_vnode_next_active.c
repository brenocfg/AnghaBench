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
struct mount {int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_activevnodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VI_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct vnode*,struct vnode*,int /*<<< orphan*/ ) ; 
 struct vnode* TAILQ_NEXT (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_ACTIVE ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VI_TRYLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 scalar_t__ VMARKER ; 
 int /*<<< orphan*/  mnt_vnode_markerfree_active (struct vnode**,struct mount*) ; 
 int /*<<< orphan*/  mnt_vnode_next_active_relock (struct vnode*,struct mount*,struct vnode*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_actfreelist ; 

__attribute__((used)) static struct vnode *
mnt_vnode_next_active(struct vnode **mvp, struct mount *mp)
{
	struct vnode *vp, *nvp;

	mtx_assert(&mp->mnt_listmtx, MA_OWNED);
	KASSERT((*mvp)->v_mount == mp, ("marker vnode mount list mismatch"));
restart:
	vp = TAILQ_NEXT(*mvp, v_actfreelist);
	while (vp != NULL) {
		if (vp->v_type == VMARKER) {
			vp = TAILQ_NEXT(vp, v_actfreelist);
			continue;
		}
		/*
		 * Try-lock because this is the wrong lock order.  If that does
		 * not succeed, drop the mount vnode list lock and try to
		 * reacquire it and the vnode interlock in the right order.
		 */
		if (!VI_TRYLOCK(vp) &&
		    !mnt_vnode_next_active_relock(*mvp, mp, vp))
			goto restart;
		KASSERT(vp->v_type != VMARKER, ("locked marker %p", vp));
		KASSERT(vp->v_mount == mp || vp->v_mount == NULL,
		    ("alien vnode on the active list %p %p", vp, mp));
		if (vp->v_mount == mp && (vp->v_iflag & VI_DOOMED) == 0)
			break;
		nvp = TAILQ_NEXT(vp, v_actfreelist);
		VI_UNLOCK(vp);
		vp = nvp;
	}
	TAILQ_REMOVE(&mp->mnt_activevnodelist, *mvp, v_actfreelist);

	/* Check if we are done */
	if (vp == NULL) {
		mtx_unlock(&mp->mnt_listmtx);
		mnt_vnode_markerfree_active(mvp, mp);
		return (NULL);
	}
	TAILQ_INSERT_AFTER(&mp->mnt_activevnodelist, vp, *mvp, v_actfreelist);
	mtx_unlock(&mp->mnt_listmtx);
	ASSERT_VI_LOCKED(vp, "active iter");
	KASSERT((vp->v_iflag & VI_ACTIVE) != 0, ("Non-active vp %p", vp));
	return (vp);
}