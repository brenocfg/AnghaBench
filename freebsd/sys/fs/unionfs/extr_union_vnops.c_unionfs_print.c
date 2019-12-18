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
struct vop_print_args {int /*<<< orphan*/  a_vp; } ;
struct unionfs_node {scalar_t__ un_uppervp; scalar_t__ un_lowervp; } ;

/* Variables and functions */
 scalar_t__ NULLVP ; 
 struct unionfs_node* VTOUNIONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vn_printf (scalar_t__,char*) ; 

__attribute__((used)) static int
unionfs_print(struct vop_print_args *ap)
{
	struct unionfs_node *unp;
	/* struct unionfs_node_status *unsp; */

	unp = VTOUNIONFS(ap->a_vp);
	/* unionfs_get_node_status(unp, curthread, &unsp); */

	printf("unionfs_vp=%p, uppervp=%p, lowervp=%p\n",
	    ap->a_vp, unp->un_uppervp, unp->un_lowervp);
	/*
	printf("unionfs opencnt: uppervp=%d, lowervp=%d\n",
	    unsp->uns_upper_opencnt, unsp->uns_lower_opencnt);
	*/

	if (unp->un_uppervp != NULLVP)
		vn_printf(unp->un_uppervp, "unionfs: upper ");
	if (unp->un_lowervp != NULLVP)
		vn_printf(unp->un_lowervp, "unionfs: lower ");

	return (0);
}