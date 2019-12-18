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
struct thread {int td_dbgflags; struct proc* td_proc; } ;
struct proc {int p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ P_SHOULDSTOP (struct proc*) ; 
 int P_TRACED ; 
 int TDB_SUSPEND ; 
 struct thread* curthread ; 

bool
thread_suspend_check_needed(void)
{
	struct proc *p;
	struct thread *td;

	td = curthread;
	p = td->td_proc;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	return (P_SHOULDSTOP(p) || ((p->p_flag & P_TRACED) != 0 &&
	    (td->td_dbgflags & TDB_SUSPEND) != 0));
}