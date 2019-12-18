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
struct thread {int td_pri_class; int td_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rq_queues; } ;
struct tdq {int tdq_idx; int tdq_ridx; TYPE_1__ tdq_timeshare; int /*<<< orphan*/  tdq_load; int /*<<< orphan*/  tdq_switchcnt; int /*<<< orphan*/  tdq_oldswitchcnt; } ;
struct td_sched {scalar_t__ ts_slice; int /*<<< orphan*/  ts_runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PRI_BASE (int) ; 
 int PRI_FIFO_BIT ; 
 scalar_t__ PRI_TIMESHARE ; 
 int RQ_NQS ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int TDF_NEEDRESCHED ; 
 int TDF_SLICEEND ; 
 struct tdq* TDQ_SELF () ; 
 int /*<<< orphan*/  TD_IS_IDLETHREAD (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct tdq* balance_tdq ; 
 scalar_t__ balance_ticks ; 
 scalar_t__ rebalance ; 
 int /*<<< orphan*/  sched_balance () ; 
 int /*<<< orphan*/  sched_interact_update (struct thread*) ; 
 int /*<<< orphan*/  sched_pctcpu_update (struct td_sched*,int) ; 
 int /*<<< orphan*/  sched_priority (struct thread*) ; 
 scalar_t__ smp_started ; 
 struct td_sched* td_get_sched (struct thread*) ; 
 scalar_t__ tdq_slice (struct tdq*) ; 
 scalar_t__ tickincr ; 

void
sched_clock(struct thread *td)
{
	struct tdq *tdq;
	struct td_sched *ts;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	tdq = TDQ_SELF();
#ifdef SMP
	/*
	 * We run the long term load balancer infrequently on the first cpu.
	 */
	if (balance_tdq == tdq && smp_started != 0 && rebalance != 0) {
		if (balance_ticks && --balance_ticks == 0)
			sched_balance();
	}
#endif
	/*
	 * Save the old switch count so we have a record of the last ticks
	 * activity.   Initialize the new switch count based on our load.
	 * If there is some activity seed it to reflect that.
	 */
	tdq->tdq_oldswitchcnt = tdq->tdq_switchcnt;
	tdq->tdq_switchcnt = tdq->tdq_load;
	/*
	 * Advance the insert index once for each tick to ensure that all
	 * threads get a chance to run.
	 */
	if (tdq->tdq_idx == tdq->tdq_ridx) {
		tdq->tdq_idx = (tdq->tdq_idx + 1) % RQ_NQS;
		if (TAILQ_EMPTY(&tdq->tdq_timeshare.rq_queues[tdq->tdq_ridx]))
			tdq->tdq_ridx = tdq->tdq_idx;
	}
	ts = td_get_sched(td);
	sched_pctcpu_update(ts, 1);
	if (td->td_pri_class & PRI_FIFO_BIT)
		return;
	if (PRI_BASE(td->td_pri_class) == PRI_TIMESHARE) {
		/*
		 * We used a tick; charge it to the thread so
		 * that we can compute our interactivity.
		 */
		td_get_sched(td)->ts_runtime += tickincr;
		sched_interact_update(td);
		sched_priority(td);
	}

	/*
	 * Force a context switch if the current thread has used up a full
	 * time slice (default is 100ms).
	 */
	if (!TD_IS_IDLETHREAD(td) && ++ts->ts_slice >= tdq_slice(tdq)) {
		ts->ts_slice = 0;
		td->td_flags |= TDF_NEEDRESCHED | TDF_SLICEEND;
	}
}