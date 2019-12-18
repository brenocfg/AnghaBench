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
struct thread {int /*<<< orphan*/  td_flags; } ;
struct td_sched {int /*<<< orphan*/  ts_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_PREEMPT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SRQ_BORING ; 
 int /*<<< orphan*/  TDF_NEEDRESCHED ; 
 int /*<<< orphan*/  TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_ON_RUNQ (struct thread*) ; 
 scalar_t__ THREAD_CAN_SCHED (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  ipi_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_rem (struct thread*) ; 
 struct td_sched* td_get_sched (struct thread*) ; 

void
sched_affinity(struct thread *td)
{
#ifdef SMP
	struct td_sched *ts;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	ts = td_get_sched(td);
	if (THREAD_CAN_SCHED(td, ts->ts_cpu))
		return;
	if (TD_ON_RUNQ(td)) {
		sched_rem(td);
		sched_add(td, SRQ_BORING);
		return;
	}
	if (!TD_IS_RUNNING(td))
		return;
	/*
	 * Force a switch before returning to userspace.  If the
	 * target thread is not running locally send an ipi to force
	 * the issue.
	 */
	td->td_flags |= TDF_NEEDRESCHED;
	if (td != curthread)
		ipi_cpu(ts->ts_cpu, IPI_PREEMPT);
#endif
}