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
struct vop_write_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_ioflag; int /*<<< orphan*/  a_uio; int /*<<< orphan*/  a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (int /*<<< orphan*/ ) ; 
 struct vnode* NULLVP ; 
 int VOP_WRITE (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unionfs_write(struct vop_write_args *ap)
{
	int		error;
	struct unionfs_node *unp;
	struct vnode   *tvp;

	/* UNIONFS_INTERNAL_DEBUG("unionfs_write: enter\n"); */

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	unp = VTOUNIONFS(ap->a_vp);
	tvp = (unp->un_uppervp != NULLVP ? unp->un_uppervp : unp->un_lowervp);

	error = VOP_WRITE(tvp, ap->a_uio, ap->a_ioflag, ap->a_cred);

	/* UNIONFS_INTERNAL_DEBUG("unionfs_write: leave (%d)\n", error); */

	return (error);
}