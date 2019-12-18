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
struct vop_advlock_args {int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_fl; int /*<<< orphan*/  a_op; int /*<<< orphan*/  a_id; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node_status {scalar_t__ uns_lower_opencnt; int /*<<< orphan*/  uns_lower_openmode; int /*<<< orphan*/  uns_upper_opencnt; } ;
struct unionfs_node {int /*<<< orphan*/  un_lowervp; struct vnode* un_uppervp; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 int LK_RETRY ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int VOP_ADVLOCK (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_CLOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int VOP_OPEN (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 
 struct thread* curthread ; 
 int unionfs_copyfile (struct unionfs_node*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  unionfs_get_node_status (struct unionfs_node*,struct thread*,struct unionfs_node_status**) ; 
 int /*<<< orphan*/  unionfs_tryrem_node_status (struct unionfs_node*,struct unionfs_node_status*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
unionfs_advlock(struct vop_advlock_args *ap)
{
	int error;
	struct unionfs_node *unp;
	struct unionfs_node_status *unsp;
	struct vnode   *vp;
	struct vnode   *uvp;
	struct thread  *td;

	UNIONFS_INTERNAL_DEBUG("unionfs_advlock: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_vp);

	vp = ap->a_vp;
	td = curthread;

	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);

	unp = VTOUNIONFS(ap->a_vp);
	uvp = unp->un_uppervp;

	if (uvp == NULLVP) {
		error = unionfs_copyfile(unp, 1, td->td_ucred, td);
		if (error != 0)
			goto unionfs_advlock_abort;
		uvp = unp->un_uppervp;

		unionfs_get_node_status(unp, td, &unsp);
		if (unsp->uns_lower_opencnt > 0) {
			/* try reopen the vnode */
			error = VOP_OPEN(uvp, unsp->uns_lower_openmode,
				td->td_ucred, td, NULL);
			if (error)
				goto unionfs_advlock_abort;
			unsp->uns_upper_opencnt++;
			VOP_CLOSE(unp->un_lowervp, unsp->uns_lower_openmode, td->td_ucred, td);
			unsp->uns_lower_opencnt--;
		} else
			unionfs_tryrem_node_status(unp, unsp);
	}

	VOP_UNLOCK(vp, LK_RELEASE);

	error = VOP_ADVLOCK(uvp, ap->a_id, ap->a_op, ap->a_fl, ap->a_flags);

	UNIONFS_INTERNAL_DEBUG("unionfs_advlock: leave (%d)\n", error);

	return error;

unionfs_advlock_abort:
	VOP_UNLOCK(vp, LK_RELEASE);

	UNIONFS_INTERNAL_DEBUG("unionfs_advlock: leave (%d)\n", error);

	return error;
}