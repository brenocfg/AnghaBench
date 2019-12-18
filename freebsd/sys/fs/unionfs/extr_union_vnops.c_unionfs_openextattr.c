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
struct vop_openextattr_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node {int un_flag; struct vnode* un_uppervp; struct vnode* un_lowervp; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_DOWNGRADE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_UPGRADE ; 
 struct vnode* NULLVP ; 
 int UNIONFS_OPENEXTL ; 
 int UNIONFS_OPENEXTU ; 
 int VOP_OPENEXTATTR (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 scalar_t__ vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
unionfs_openextattr(struct vop_openextattr_args *ap)
{
	int		error;
	struct unionfs_node *unp;
	struct vnode   *vp;
	struct vnode   *tvp;

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	vp = ap->a_vp;
	unp = VTOUNIONFS(vp);
	tvp = (unp->un_uppervp != NULLVP ? unp->un_uppervp : unp->un_lowervp);

	if ((tvp == unp->un_uppervp && (unp->un_flag & UNIONFS_OPENEXTU)) ||
	    (tvp == unp->un_lowervp && (unp->un_flag & UNIONFS_OPENEXTL)))
		return (EBUSY);

	error = VOP_OPENEXTATTR(tvp, ap->a_cred, ap->a_td);

	if (error == 0) {
		if (vn_lock(vp, LK_UPGRADE) != 0)
			vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		if (tvp == unp->un_uppervp)
			unp->un_flag |= UNIONFS_OPENEXTU;
		else
			unp->un_flag |= UNIONFS_OPENEXTL;
		vn_lock(vp, LK_DOWNGRADE | LK_RETRY);
	}

	return (error);
}