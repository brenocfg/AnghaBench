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
typedef  int u_char ;
struct thread {int td_priority; } ;
struct tdq {int tdq_idx; int tdq_ridx; int /*<<< orphan*/  tdq_idle; int /*<<< orphan*/  tdq_timeshare; int /*<<< orphan*/  tdq_realtime; int /*<<< orphan*/  tdq_transferable; } ;
struct td_sched {int /*<<< orphan*/ * ts_runq; int /*<<< orphan*/  ts_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PRI_BATCH_RANGE ; 
 int PRI_MAX_BATCH ; 
 int PRI_MIN_BATCH ; 
 int RQ_NQS ; 
 int SRQ_BORROWING ; 
 int SRQ_PREEMPTED ; 
 int /*<<< orphan*/  TDQ_LOCK_ASSERT (struct tdq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_SET_RUNQ (struct thread*) ; 
 scalar_t__ THREAD_CAN_MIGRATE (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSF_XFERABLE ; 
 int /*<<< orphan*/  runq_add (int /*<<< orphan*/ *,struct thread*,int) ; 
 int /*<<< orphan*/  runq_add_pri (int /*<<< orphan*/ *,struct thread*,int,int) ; 
 struct td_sched* td_get_sched (struct thread*) ; 

__attribute__((used)) static __inline void
tdq_runq_add(struct tdq *tdq, struct thread *td, int flags)
{
	struct td_sched *ts;
	u_char pri;

	TDQ_LOCK_ASSERT(tdq, MA_OWNED);
	THREAD_LOCK_ASSERT(td, MA_OWNED);

	pri = td->td_priority;
	ts = td_get_sched(td);
	TD_SET_RUNQ(td);
	if (THREAD_CAN_MIGRATE(td)) {
		tdq->tdq_transferable++;
		ts->ts_flags |= TSF_XFERABLE;
	}
	if (pri < PRI_MIN_BATCH) {
		ts->ts_runq = &tdq->tdq_realtime;
	} else if (pri <= PRI_MAX_BATCH) {
		ts->ts_runq = &tdq->tdq_timeshare;
		KASSERT(pri <= PRI_MAX_BATCH && pri >= PRI_MIN_BATCH,
			("Invalid priority %d on timeshare runq", pri));
		/*
		 * This queue contains only priorities between MIN and MAX
		 * realtime.  Use the whole queue to represent these values.
		 */
		if ((flags & (SRQ_BORROWING|SRQ_PREEMPTED)) == 0) {
			pri = RQ_NQS * (pri - PRI_MIN_BATCH) / PRI_BATCH_RANGE;
			pri = (pri + tdq->tdq_idx) % RQ_NQS;
			/*
			 * This effectively shortens the queue by one so we
			 * can have a one slot difference between idx and
			 * ridx while we wait for threads to drain.
			 */
			if (tdq->tdq_ridx != tdq->tdq_idx &&
			    pri == tdq->tdq_ridx)
				pri = (unsigned char)(pri - 1) % RQ_NQS;
		} else
			pri = tdq->tdq_ridx;
		runq_add_pri(ts->ts_runq, td, pri, flags);
		return;
	} else
		ts->ts_runq = &tdq->tdq_idle;
	runq_add(ts->ts_runq, td, flags);
}