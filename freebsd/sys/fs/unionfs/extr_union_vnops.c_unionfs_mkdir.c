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
struct vop_mkdir_args {int /*<<< orphan*/  a_vpp; TYPE_1__* a_dvp; int /*<<< orphan*/  a_vap; struct componentname* a_cnp; } ;
struct vnode {int dummy; } ;
struct vattr {int va_flags; } ;
struct unionfs_node {struct vnode* un_uppervp; } ;
struct thread {int dummy; } ;
struct componentname {int cn_lkflags; int cn_flags; int /*<<< orphan*/  cn_cred; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int EROFS ; 
 int ISWHITEOUT ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (TYPE_1__*) ; 
 int LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 struct vnode* NULLVP ; 
 int OPAQUE ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int VOP_MKDIR (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (TYPE_1__*) ; 
 struct thread* curthread ; 
 int unionfs_nodeget (int /*<<< orphan*/ ,struct vnode*,struct vnode*,TYPE_1__*,int /*<<< orphan*/ ,struct componentname*,struct thread*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
unionfs_mkdir(struct vop_mkdir_args *ap)
{
	int		error;
	int		lkflags;
	struct unionfs_node *dunp;
	struct componentname *cnp;
	struct thread  *td;
	struct vnode   *udvp;
	struct vnode   *uvp;
	struct vattr	va;

	UNIONFS_INTERNAL_DEBUG("unionfs_mkdir: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_dvp);

	error = EROFS;
	dunp = VTOUNIONFS(ap->a_dvp);
	cnp = ap->a_cnp;
	lkflags = cnp->cn_lkflags;
	td = curthread;
	udvp = dunp->un_uppervp;

	if (udvp != NULLVP) {
		/* check opaque */
		if (!(cnp->cn_flags & ISWHITEOUT)) {
			error = VOP_GETATTR(udvp, &va, cnp->cn_cred);
			if (error != 0)
				return (error);
			if (va.va_flags & OPAQUE) 
				cnp->cn_flags |= ISWHITEOUT;
		}

		if ((error = VOP_MKDIR(udvp, &uvp, cnp, ap->a_vap)) == 0) {
			VOP_UNLOCK(uvp, LK_RELEASE);
			cnp->cn_lkflags = LK_EXCLUSIVE;
			error = unionfs_nodeget(ap->a_dvp->v_mount, uvp, NULLVP,
			    ap->a_dvp, ap->a_vpp, cnp, td);
			cnp->cn_lkflags = lkflags;
			vrele(uvp);
		}
	}

	UNIONFS_INTERNAL_DEBUG("unionfs_mkdir: leave (%d)\n", error);

	return (error);
}