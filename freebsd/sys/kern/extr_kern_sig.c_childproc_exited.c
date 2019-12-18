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
struct proc {int p_xexit; int /*<<< orphan*/  p_xsig; } ;

/* Variables and functions */
 int CLD_DUMPED ; 
 int CLD_EXITED ; 
 int CLD_KILLED ; 
 scalar_t__ WCOREDUMP (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int WTERMSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigparent (struct proc*,int,int) ; 

void
childproc_exited(struct proc *p)
{
	int reason, status;

	if (WCOREDUMP(p->p_xsig)) {
		reason = CLD_DUMPED;
		status = WTERMSIG(p->p_xsig);
	} else if (WIFSIGNALED(p->p_xsig)) {
		reason = CLD_KILLED;
		status = WTERMSIG(p->p_xsig);
	} else {
		reason = CLD_EXITED;
		status = p->p_xexit;
	}
	/*
	 * XXX avoid calling wakeup(p->p_pptr), the work is
	 * done in exit1().
	 */
	sigparent(p, reason, status);
}