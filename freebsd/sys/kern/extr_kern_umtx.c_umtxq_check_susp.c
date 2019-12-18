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
struct thread {int td_flags; int td_dbgflags; struct proc* td_proc; } ;
struct proc {int p_flag; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ P_SHOULDSTOP (struct proc*) ; 
 int P_SINGLE_EXIT ; 
 int P_TRACED ; 
 int TDB_SUSPEND ; 
 int TDF_NEEDSUSPCHK ; 
 int thread_suspend_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umtxq_check_susp(struct thread *td, bool sleep)
{
	struct proc *p;
	int error;

	/*
	 * The check for TDF_NEEDSUSPCHK is racy, but it is enough to
	 * eventually break the lockstep loop.
	 */
	if ((td->td_flags & TDF_NEEDSUSPCHK) == 0)
		return (0);
	error = 0;
	p = td->td_proc;
	PROC_LOCK(p);
	if (p->p_flag & P_SINGLE_EXIT)
		error = EINTR;
	else if (P_SHOULDSTOP(p) ||
	    ((p->p_flag & P_TRACED) && (td->td_dbgflags & TDB_SUSPEND)))
		error = sleep ? thread_suspend_check(0) : ERESTART;
	PROC_UNLOCK(p);
	return (error);
}