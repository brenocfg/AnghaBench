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
struct vop_getextattr_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_size; int /*<<< orphan*/  a_uio; int /*<<< orphan*/  a_name; int /*<<< orphan*/  a_attrnamespace; struct vnode* a_vp; } ;
struct vnode {struct pfs_vdata* v_data; } ;
struct proc {int dummy; } ;
struct pfs_vdata {int /*<<< orphan*/  pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {int /*<<< orphan*/ * pn_getextattr; int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_visible (int /*<<< orphan*/ ,struct pfs_node*,int /*<<< orphan*/ ,struct proc**) ; 
 int pn_getextattr (int /*<<< orphan*/ ,struct proc*,struct pfs_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfs_getextattr(struct vop_getextattr_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct pfs_node *pn = pvd->pvd_pn;
	struct proc *proc;
	int error;

	PFS_TRACE(("%s", pn->pn_name));
	pfs_assert_not_owned(pn);

	/*
	 * This is necessary because either process' privileges may
	 * have changed since the open() call.
	 */
	if (!pfs_visible(curthread, pn, pvd->pvd_pid, &proc))
		PFS_RETURN (EIO);

	if (pn->pn_getextattr == NULL)
		error = EOPNOTSUPP;
	else
		error = pn_getextattr(curthread, proc, pn,
		    va->a_attrnamespace, va->a_name, va->a_uio,
		    va->a_size, va->a_cred);

	if (proc != NULL)
		PROC_UNLOCK(proc);

	PFS_RETURN (error);
}