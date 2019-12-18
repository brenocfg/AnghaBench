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
struct vop_unlock_args {int a_flags; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node {struct vnode* un_uppervp; struct vnode* un_lowervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_RELEASE ; 
 struct vnode* NULLVP ; 
 int VOP_UNLOCK (struct vnode*,int) ; 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vholdnz (struct vnode*) ; 
 int vop_stdunlock (struct vop_unlock_args*) ; 

__attribute__((used)) static int
unionfs_unlock(struct vop_unlock_args *ap)
{
	int		error;
	int		flags;
	int		uhold;
	struct vnode   *vp;
	struct vnode   *lvp;
	struct vnode   *uvp;
	struct unionfs_node *unp;

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	error = 0;
	uhold = 0;
	flags = ap->a_flags | LK_RELEASE;
	vp = ap->a_vp;

	unp = VTOUNIONFS(vp);
	if (unp == NULL)
		goto unionfs_unlock_null_vnode;
	lvp = unp->un_lowervp;
	uvp = unp->un_uppervp;

	if (lvp != NULLVP) {
		vholdnz(lvp);
		error = VOP_UNLOCK(lvp, flags);
	}

	if (error == 0 && uvp != NULLVP) {
		vholdnz(uvp);
		uhold = 1;
		error = VOP_UNLOCK(uvp, flags);
	}

	if (lvp != NULLVP)
		vdrop(lvp);
	if (uhold != 0)
		vdrop(uvp);

	return error;

unionfs_unlock_null_vnode:
	return (vop_stdunlock(ap));
}