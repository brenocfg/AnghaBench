#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_name; } ;
struct tdq {int dummy; } ;
struct mtx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ts_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ABSENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct tdq* TDQ_CPU (int /*<<< orphan*/ ) ; 
 struct mtx* TDQ_LOCKPTR (struct tdq*) ; 
 int /*<<< orphan*/  TDQ_UNLOCK (struct tdq*) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 
 TYPE_1__* td_get_sched (struct thread*) ; 
 int /*<<< orphan*/  tdq_add (struct tdq*,struct thread*,int) ; 
 int /*<<< orphan*/  tdq_load_rem (struct tdq*,struct thread*) ; 
 int /*<<< orphan*/  tdq_lock_pair (struct tdq*,struct tdq*) ; 
 int /*<<< orphan*/  tdq_notify (struct tdq*,struct thread*) ; 
 int /*<<< orphan*/  thread_lock_block (struct thread*) ; 

__attribute__((used)) static struct mtx *
sched_switch_migrate(struct tdq *tdq, struct thread *td, int flags)
{
	struct tdq *tdn;

	KASSERT(!CPU_ABSENT(td_get_sched(td)->ts_cpu), ("sched_switch_migrate: "
	    "thread %s queued on absent CPU %d.", td->td_name,
	    td_get_sched(td)->ts_cpu));
	tdn = TDQ_CPU(td_get_sched(td)->ts_cpu);
#ifdef SMP
	tdq_load_rem(tdq, td);
	/*
	 * Do the lock dance required to avoid LOR.  We grab an extra
	 * spinlock nesting to prevent preemption while we're
	 * not holding either run-queue lock.
	 */
	spinlock_enter();
	thread_lock_block(td);	/* This releases the lock on tdq. */

	/*
	 * Acquire both run-queue locks before placing the thread on the new
	 * run-queue to avoid deadlocks created by placing a thread with a
	 * blocked lock on the run-queue of a remote processor.  The deadlock
	 * occurs when a third processor attempts to lock the two queues in
	 * question while the target processor is spinning with its own
	 * run-queue lock held while waiting for the blocked lock to clear.
	 */
	tdq_lock_pair(tdn, tdq);
	tdq_add(tdn, td, flags);
	tdq_notify(tdn, td);
	TDQ_UNLOCK(tdn);
	spinlock_exit();
#endif
	return (TDQ_LOCKPTR(tdn));
}