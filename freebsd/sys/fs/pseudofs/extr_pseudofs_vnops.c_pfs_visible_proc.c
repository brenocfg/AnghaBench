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
struct proc {int p_flag; } ;
struct pfs_node {int /*<<< orphan*/ * pn_vis; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int P_WEXIT ; 
 scalar_t__ p_cansee (struct thread*,struct proc*) ; 
 int pn_vis (struct thread*,struct proc*,struct pfs_node*) ; 

__attribute__((used)) static int
pfs_visible_proc(struct thread *td, struct pfs_node *pn, struct proc *proc)
{
	int visible;

	if (proc == NULL)
		return (0);

	PROC_LOCK_ASSERT(proc, MA_OWNED);

	visible = ((proc->p_flag & P_WEXIT) == 0);
	if (visible)
		visible = (p_cansee(td, proc) == 0);
	if (visible && pn->pn_vis != NULL)
		visible = pn_vis(td, proc, pn);
	if (!visible)
		return (0);
	return (1);
}