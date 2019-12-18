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
struct vop_rename_args {struct vnode* a_tvp; struct vnode* a_fdvp; struct vnode* a_fvp; struct vnode* a_tdvp; } ;
struct vop_generic_args {int dummy; } ;
struct vnode {scalar_t__ v_mount; } ;
struct null_node {int /*<<< orphan*/  null_flags; } ;

/* Variables and functions */
 int EXDEV ; 
 int /*<<< orphan*/  NULLV_DROP ; 
 struct null_node* VTONULL (struct vnode*) ; 
 int null_bypass (struct vop_generic_args*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
null_rename(struct vop_rename_args *ap)
{
	struct vnode *tdvp = ap->a_tdvp;
	struct vnode *fvp = ap->a_fvp;
	struct vnode *fdvp = ap->a_fdvp;
	struct vnode *tvp = ap->a_tvp;
	struct null_node *tnn;

	/* Check for cross-device rename. */
	if ((fvp->v_mount != tdvp->v_mount) ||
	    (tvp && (fvp->v_mount != tvp->v_mount))) {
		if (tdvp == tvp)
			vrele(tdvp);
		else
			vput(tdvp);
		if (tvp)
			vput(tvp);
		vrele(fdvp);
		vrele(fvp);
		return (EXDEV);
	}

	if (tvp != NULL) {
		tnn = VTONULL(tvp);
		tnn->null_flags |= NULLV_DROP;
	}
	return (null_bypass((struct vop_generic_args *)ap));
}