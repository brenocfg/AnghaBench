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
struct thread {int /*<<< orphan*/  td_flags; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_suspcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_SLOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDF_NEEDSUSPCHK ; 
 int /*<<< orphan*/  TD_IS_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  TD_SET_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_sleep (struct thread*,int /*<<< orphan*/ ) ; 

void
thread_suspend_one(struct thread *td)
{
	struct proc *p;

	p = td->td_proc;
	PROC_SLOCK_ASSERT(p, MA_OWNED);
	THREAD_LOCK_ASSERT(td, MA_OWNED);
	KASSERT(!TD_IS_SUSPENDED(td), ("already suspended"));
	p->p_suspcount++;
	td->td_flags &= ~TDF_NEEDSUSPCHK;
	TD_SET_SUSPENDED(td);
	sched_sleep(td, 0);
}