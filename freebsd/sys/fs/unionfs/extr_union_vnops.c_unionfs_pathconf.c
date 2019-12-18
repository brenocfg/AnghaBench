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
struct vop_pathconf_args {int /*<<< orphan*/  a_retval; int /*<<< orphan*/  a_name; int /*<<< orphan*/  a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (int /*<<< orphan*/ ) ; 
 struct vnode* NULLVP ; 
 int VOP_PATHCONF (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unionfs_pathconf(struct vop_pathconf_args *ap)
{
	struct unionfs_node *unp;
	struct vnode   *vp;

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	unp = VTOUNIONFS(ap->a_vp);
	vp = (unp->un_uppervp != NULLVP ? unp->un_uppervp : unp->un_lowervp);

	return (VOP_PATHCONF(vp, ap->a_name, ap->a_retval));
}