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
struct vop_ioctl_args {int /*<<< orphan*/  a_data; int /*<<< orphan*/  a_command; struct vnode* a_vp; } ;
struct vnode {int v_iflag; scalar_t__ v_type; struct pfs_vdata* v_data; } ;
struct proc {int dummy; } ;
struct pfs_vdata {int /*<<< orphan*/  pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {int /*<<< orphan*/ * pn_ioctl; int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EIO ; 
 int ENOTTY ; 
 int /*<<< orphan*/  KASSERT_PN_IS_FILE (struct pfs_node*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_visible (int /*<<< orphan*/ ,struct pfs_node*,int /*<<< orphan*/ ,struct proc**) ; 
 int pn_ioctl (int /*<<< orphan*/ ,struct proc*,struct pfs_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
pfs_ioctl(struct vop_ioctl_args *va)
{
	struct vnode *vn;
	struct pfs_vdata *pvd;
	struct pfs_node *pn;
	struct proc *proc;
	int error;

	vn = va->a_vp;
	vn_lock(vn, LK_SHARED | LK_RETRY);
	if (vn->v_iflag & VI_DOOMED) {
		VOP_UNLOCK(vn, 0);
		return (EBADF);
	}
	pvd = vn->v_data;
	pn = pvd->pvd_pn;

	PFS_TRACE(("%s: %lx", pn->pn_name, va->a_command));
	pfs_assert_not_owned(pn);

	if (vn->v_type != VREG) {
		VOP_UNLOCK(vn, 0);
		PFS_RETURN (EINVAL);
	}
	KASSERT_PN_IS_FILE(pn);

	if (pn->pn_ioctl == NULL) {
		VOP_UNLOCK(vn, 0);
		PFS_RETURN (ENOTTY);
	}

	/*
	 * This is necessary because process' privileges may
	 * have changed since the open() call.
	 */
	if (!pfs_visible(curthread, pn, pvd->pvd_pid, &proc)) {
		VOP_UNLOCK(vn, 0);
		PFS_RETURN (EIO);
	}

	error = pn_ioctl(curthread, proc, pn, va->a_command, va->a_data);

	if (proc != NULL)
		PROC_UNLOCK(proc);

	VOP_UNLOCK(vn, 0);
	PFS_RETURN (error);
}