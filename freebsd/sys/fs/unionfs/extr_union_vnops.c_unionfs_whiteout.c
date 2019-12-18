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
struct vop_whiteout_args {int a_flags; struct componentname* a_cnp; int /*<<< orphan*/  a_dvp; } ;
struct vnode {int dummy; } ;
struct unionfs_node {struct vnode* un_uppervp; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
#define  CREATE 130 
#define  DELETE 129 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (int /*<<< orphan*/ ) ; 
#define  LOOKUP 128 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int VOP_WHITEOUT (struct vnode*,struct componentname*,int) ; 
 struct unionfs_node* VTOUNIONFS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unionfs_whiteout(struct vop_whiteout_args *ap)
{
	struct unionfs_node *dunp;
	struct componentname *cnp;
	struct vnode   *udvp;
	int		error;

	UNIONFS_INTERNAL_DEBUG("unionfs_whiteout: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_dvp);

	dunp = VTOUNIONFS(ap->a_dvp);
	cnp = ap->a_cnp;
	udvp = dunp->un_uppervp;
	error = EOPNOTSUPP;

	if (udvp != NULLVP) {
		switch (ap->a_flags) {
		case CREATE:
		case DELETE:
		case LOOKUP:
			error = VOP_WHITEOUT(udvp, cnp, ap->a_flags);
			break;
		default:
			error = EINVAL;
			break;
		}
	}

	UNIONFS_INTERNAL_DEBUG("unionfs_whiteout: leave (%d)\n", error);

	return (error);
}