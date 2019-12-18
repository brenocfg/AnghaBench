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
struct proc {int p_flag; int /*<<< orphan*/  p_siglist; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_KPROC ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
kproc_resume(struct proc *p)
{
	/*
	 * Make sure this is indeed a system process and we can safely
	 * use the p_siglist field.
	 */
	PROC_LOCK(p);
	if ((p->p_flag & P_KPROC) == 0) {
		PROC_UNLOCK(p);
		return (EINVAL);
	}
	SIGDELSET(p->p_siglist, SIGSTOP);
	PROC_UNLOCK(p);
	wakeup(&p->p_siglist);
	return (0);
}