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
struct vop_close_args {int /*<<< orphan*/  a_td; struct vnode* a_vp; } ;
struct vnode {struct pfs_vdata* v_data; } ;
struct proc {int dummy; } ;
struct pfs_vdata {scalar_t__ pvd_pid; struct pfs_node* pvd_pn; } ;
struct pfs_node {int /*<<< orphan*/ * pn_close; int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 scalar_t__ NO_PID ; 
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct proc* pfind (scalar_t__) ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 
 int pn_close (int /*<<< orphan*/ ,struct proc*,struct pfs_node*) ; 
 int vrefcnt (struct vnode*) ; 

__attribute__((used)) static int
pfs_close(struct vop_close_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct pfs_node *pn = pvd->pvd_pn;
	struct proc *proc;
	int error;

	PFS_TRACE(("%s", pn->pn_name));
	pfs_assert_not_owned(pn);

	/*
	 * Do nothing unless this is the last close and the node has a
	 * last-close handler.
	 */
	if (vrefcnt(vn) > 1 || pn->pn_close == NULL)
		PFS_RETURN (0);

	if (pvd->pvd_pid != NO_PID) {
		proc = pfind(pvd->pvd_pid);
	} else {
		proc = NULL;
	}

	error = pn_close(va->a_td, proc, pn);

	if (proc != NULL)
		PROC_UNLOCK(proc);

	PFS_RETURN (error);
}