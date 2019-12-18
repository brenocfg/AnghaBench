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
typedef  int /*<<< orphan*/  u_char ;
struct thread {int td_pinned; int /*<<< orphan*/  td_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_GIANT () ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 scalar_t__ RCU_SKIP () ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ck_epoch_synchronize_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuid ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  linux_epoch ; 
 int /*<<< orphan*/  linux_synchronize_rcu_cb ; 
 int /*<<< orphan*/  sched_bind (struct thread*,int) ; 
 int sched_is_bound (struct thread*) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_unbind (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
linux_synchronize_rcu(void)
{
	struct thread *td;
	int was_bound;
	int old_cpu;
	int old_pinned;
	u_char old_prio;

	if (RCU_SKIP())
		return;

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "linux_synchronize_rcu() can sleep");

	td = curthread;

	/*
	 * Synchronizing RCU might change the CPU core this function
	 * is running on. Save current values:
	 */
	thread_lock(td);

	DROP_GIANT();

	old_cpu = PCPU_GET(cpuid);
	old_pinned = td->td_pinned;
	old_prio = td->td_priority;
	was_bound = sched_is_bound(td);
	sched_unbind(td);
	td->td_pinned = 0;
	sched_bind(td, old_cpu);

	ck_epoch_synchronize_wait(&linux_epoch,
	    &linux_synchronize_rcu_cb, NULL);

	/* restore CPU binding, if any */
	if (was_bound != 0) {
		sched_bind(td, old_cpu);
	} else {
		/* get thread back to initial CPU, if any */
		if (old_pinned != 0)
			sched_bind(td, old_cpu);
		sched_unbind(td);
	}
	/* restore pinned after bind */
	td->td_pinned = old_pinned;

	/* restore thread priority */
	sched_prio(td, old_prio);
	thread_unlock(td);

	PICKUP_GIANT();
}