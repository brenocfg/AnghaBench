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
struct vop_getacl_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_aclp; int /*<<< orphan*/  a_type; int /*<<< orphan*/  a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (int /*<<< orphan*/ ) ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int VOP_GETACL (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unionfs_getacl(struct vop_getacl_args *ap)
{
	int		error;
	struct unionfs_node *unp;
	struct vnode   *vp;

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	unp = VTOUNIONFS(ap->a_vp);
	vp = (unp->un_uppervp != NULLVP ? unp->un_uppervp : unp->un_lowervp);

	UNIONFS_INTERNAL_DEBUG("unionfs_getacl: enter\n");

	error = VOP_GETACL(vp, ap->a_type, ap->a_aclp, ap->a_cred, ap->a_td);

	UNIONFS_INTERNAL_DEBUG("unionfs_getacl: leave (%d)\n", error);

	return (error);
}