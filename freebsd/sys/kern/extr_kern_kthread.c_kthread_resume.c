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
struct thread {int td_pflags; int /*<<< orphan*/  td_flags; struct proc* td_proc; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  TDF_KTH_SUSP ; 
 int TDP_KTHREAD ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
kthread_resume(struct thread *td)
{
	struct proc *p;

	p = td->td_proc;

	/*
	 * td_pflags should not be read by any thread other than
	 * curthread, but as long as this flag is invariant during the
	 * thread's lifetime, it is OK to check its state.
	 */
	if ((td->td_pflags & TDP_KTHREAD) == 0)
		return (EINVAL);

	PROC_LOCK(p);
	thread_lock(td);
	td->td_flags &= ~TDF_KTH_SUSP;
	thread_unlock(td);
	wakeup(&td->td_flags);
	PROC_UNLOCK(p);
	return (0);
}