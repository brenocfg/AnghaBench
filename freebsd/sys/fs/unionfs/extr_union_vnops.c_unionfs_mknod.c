#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vop_mknod_args {struct vnode** a_vpp; TYPE_1__* a_dvp; int /*<<< orphan*/  a_vap; struct componentname* a_cnp; } ;
struct vnode {scalar_t__ v_type; } ;
struct unionfs_node {struct vnode* un_uppervp; } ;
struct componentname {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (TYPE_1__*) ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int VOP_MKNOD (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VSOCK ; 
 struct unionfs_node* VTOUNIONFS (TYPE_1__*) ; 
 int /*<<< orphan*/  curthread ; 
 int unionfs_nodeget (int /*<<< orphan*/ ,struct vnode*,struct vnode*,TYPE_1__*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
unionfs_mknod(struct vop_mknod_args *ap)
{
	struct unionfs_node *dunp;
	struct componentname *cnp;
	struct vnode   *udvp;
	struct vnode   *vp;
	int		error;

	UNIONFS_INTERNAL_DEBUG("unionfs_mknod: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_dvp);

	dunp = VTOUNIONFS(ap->a_dvp);
	cnp = ap->a_cnp;
	udvp = dunp->un_uppervp;
	error = EROFS;

	if (udvp != NULLVP) {
		error = VOP_MKNOD(udvp, &vp, cnp, ap->a_vap);
		if (error != 0)
			goto unionfs_mknod_abort;

		if (vp->v_type == VSOCK)
			*(ap->a_vpp) = vp;
		else {
			VOP_UNLOCK(vp, LK_RELEASE);
			error = unionfs_nodeget(ap->a_dvp->v_mount, vp, NULLVP,
			    ap->a_dvp, ap->a_vpp, cnp, curthread);
			vrele(vp);
		}
	}

unionfs_mknod_abort:
	UNIONFS_INTERNAL_DEBUG("unionfs_mknod: leave (%d)\n", error);

	return (error);
}