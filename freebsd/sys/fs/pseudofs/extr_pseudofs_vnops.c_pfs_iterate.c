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
struct thread {int dummy; } ;
struct proc {int dummy; } ;
struct pfs_node {scalar_t__ pn_type; struct pfs_node* pn_next; struct pfs_node* pn_nodes; } ;

/* Variables and functions */
 struct proc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SX_SLOCKED ; 
 int /*<<< orphan*/  allproc ; 
 int /*<<< orphan*/  allproc_lock ; 
 int /*<<< orphan*/  p_list ; 
 int /*<<< orphan*/  pfs_assert_owned (struct pfs_node*) ; 
 int pfs_visible_proc (struct thread*,struct pfs_node*,struct proc*) ; 
 scalar_t__ pfstype_procdir ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfs_iterate(struct thread *td, struct proc *proc, struct pfs_node *pd,
	    struct pfs_node **pn, struct proc **p)
{
	int visible;

	sx_assert(&allproc_lock, SX_SLOCKED);
	pfs_assert_owned(pd);
 again:
	if (*pn == NULL) {
		/* first node */
		*pn = pd->pn_nodes;
	} else if ((*pn)->pn_type != pfstype_procdir) {
		/* next node */
		*pn = (*pn)->pn_next;
	}
	if (*pn != NULL && (*pn)->pn_type == pfstype_procdir) {
		/* next process */
		if (*p == NULL)
			*p = LIST_FIRST(&allproc);
		else
			*p = LIST_NEXT(*p, p_list);
		/* out of processes: next node */
		if (*p == NULL)
			*pn = (*pn)->pn_next;
		else
			PROC_LOCK(*p);
	}

	if ((*pn) == NULL)
		return (-1);

	if (*p != NULL) {
		visible = pfs_visible_proc(td, *pn, *p);
		PROC_UNLOCK(*p);
	} else if (proc != NULL) {
		visible = pfs_visible_proc(td, *pn, proc);
	} else {
		visible = 1;
	}
	if (!visible)
		goto again;

	return (0);
}