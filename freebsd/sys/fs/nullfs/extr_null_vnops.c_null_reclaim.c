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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_writecount; int /*<<< orphan*/  v_lock; int /*<<< orphan*/ * v_vnlock; int /*<<< orphan*/ * v_object; int /*<<< orphan*/ * v_data; } ;
struct null_node {int null_flags; struct vnode* null_lowervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  M_NULLFSNODE ; 
 int NULLV_NOUNLOCK ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int /*<<< orphan*/  VOP_ADD_WRITECOUNT (struct vnode*,int /*<<< orphan*/ ) ; 
 struct null_node* VTONULL (struct vnode*) ; 
 int /*<<< orphan*/  free (struct null_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_hashrem (struct null_node*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vunref (struct vnode*) ; 

__attribute__((used)) static int
null_reclaim(struct vop_reclaim_args *ap)
{
	struct vnode *vp;
	struct null_node *xp;
	struct vnode *lowervp;

	vp = ap->a_vp;
	xp = VTONULL(vp);
	lowervp = xp->null_lowervp;

	KASSERT(lowervp != NULL && vp->v_vnlock != &vp->v_lock,
	    ("Reclaiming incomplete null vnode %p", vp));

	null_hashrem(xp);
	/*
	 * Use the interlock to protect the clearing of v_data to
	 * prevent faults in null_lock().
	 */
	lockmgr(&vp->v_lock, LK_EXCLUSIVE, NULL);
	VI_LOCK(vp);
	vp->v_data = NULL;
	vp->v_object = NULL;
	vp->v_vnlock = &vp->v_lock;

	/*
	 * If we were opened for write, we leased the write reference
	 * to the lower vnode.  If this is a reclamation due to the
	 * forced unmount, undo the reference now.
	 */
	if (vp->v_writecount > 0)
		VOP_ADD_WRITECOUNT(lowervp, -vp->v_writecount);
	else if (vp->v_writecount < 0)
		vp->v_writecount = 0;

	VI_UNLOCK(vp);

	if ((xp->null_flags & NULLV_NOUNLOCK) != 0)
		vunref(lowervp);
	else
		vput(lowervp);
	free(xp, M_NULLFSNODE);

	return (0);
}