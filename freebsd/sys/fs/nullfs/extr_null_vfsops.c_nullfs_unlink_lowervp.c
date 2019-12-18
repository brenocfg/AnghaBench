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
struct vnode {scalar_t__ v_usecount; int v_iflag; } ;
struct null_node {int null_flags; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NULLV_DROP ; 
 int NULLV_NOUNLOCK ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct null_node* VTONULL (struct vnode*) ; 
 struct vnode* null_hashget (struct mount*,struct vnode*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vunref (struct vnode*) ; 

__attribute__((used)) static void
nullfs_unlink_lowervp(struct mount *mp, struct vnode *lowervp)
{
	struct vnode *vp;
	struct null_node *xp;

	vp = null_hashget(mp, lowervp);
	if (vp == NULL)
		return;
	xp = VTONULL(vp);
	xp->null_flags |= NULLV_DROP | NULLV_NOUNLOCK;
	vhold(vp);
	vunref(vp);

	if (vp->v_usecount == 0) {
		/*
		 * If vunref() dropped the last use reference on the
		 * nullfs vnode, it must be reclaimed, and its lock
		 * was split from the lower vnode lock.  Need to do
		 * extra unlock before allowing the final vdrop() to
		 * free the vnode.
		 */
		KASSERT((vp->v_iflag & VI_DOOMED) != 0,
		    ("not reclaimed nullfs vnode %p", vp));
		VOP_UNLOCK(vp, 0);
	} else {
		/*
		 * Otherwise, the nullfs vnode still shares the lock
		 * with the lower vnode, and must not be unlocked.
		 * Also clear the NULLV_NOUNLOCK, the flag is not
		 * relevant for future reclamations.
		 */
		ASSERT_VOP_ELOCKED(vp, "unlink_lowervp");
		KASSERT((vp->v_iflag & VI_DOOMED) == 0,
		    ("reclaimed nullfs vnode %p", vp));
		xp->null_flags &= ~NULLV_NOUNLOCK;
	}
	vdrop(vp);
}