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
struct vop_write_args {struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct pfs_vdata* v_data; } ;
struct uio {int dummy; } ;
struct sbuf {int dummy; } ;
struct proc {int dummy; } ;
struct pfs_vdata {int /*<<< orphan*/  pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {int pn_flags; int /*<<< orphan*/ * pn_fill; int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KASSERT_PN_IS_FILE (struct pfs_node*) ; 
 int PFS_RAWWR ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int PFS_WR ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_visible (int /*<<< orphan*/ ,struct pfs_node*,int /*<<< orphan*/ ,struct proc**) ; 
 int pn_fill (int /*<<< orphan*/ ,struct proc*,struct pfs_node*,struct sbuf*,struct uio*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_uionew (struct sbuf*,struct uio*,int*) ; 

__attribute__((used)) static int
pfs_write(struct vop_write_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct pfs_node *pn = pvd->pvd_pn;
	struct uio *uio = va->a_uio;
	struct proc *proc;
	struct sbuf sb;
	int error;

	PFS_TRACE(("%s", pn->pn_name));
	pfs_assert_not_owned(pn);

	if (vn->v_type != VREG)
		PFS_RETURN (EINVAL);
	KASSERT_PN_IS_FILE(pn);

	if (!(pn->pn_flags & PFS_WR))
		PFS_RETURN (EBADF);

	if (pn->pn_fill == NULL)
		PFS_RETURN (EIO);

	/*
	 * This is necessary because either process' privileges may
	 * have changed since the open() call.
	 */
	if (!pfs_visible(curthread, pn, pvd->pvd_pid, &proc))
		PFS_RETURN (EIO);
	if (proc != NULL) {
		_PHOLD(proc);
		PROC_UNLOCK(proc);
	}

	if (pn->pn_flags & PFS_RAWWR) {
		error = pn_fill(curthread, proc, pn, NULL, uio);
		if (proc != NULL)
			PRELE(proc);
		PFS_RETURN (error);
	}

	sbuf_uionew(&sb, uio, &error);
	if (error) {
		if (proc != NULL)
			PRELE(proc);
		PFS_RETURN (error);
	}

	error = pn_fill(curthread, proc, pn, &sb, uio);

	sbuf_delete(&sb);
	if (proc != NULL)
		PRELE(proc);
	PFS_RETURN (error);
}