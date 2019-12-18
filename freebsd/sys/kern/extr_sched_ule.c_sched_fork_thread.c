#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dr_policy; } ;
struct thread {int /*<<< orphan*/  td_base_pri; int /*<<< orphan*/  td_priority; TYPE_2__* td_cpuset; TYPE_1__ td_domain; int /*<<< orphan*/  td_lock; void* td_lastcpu; void* td_oncpu; } ;
struct tdq {int dummy; } ;
struct td_sched {int /*<<< orphan*/  ts_name; scalar_t__ ts_slice; int /*<<< orphan*/  ts_runtime; int /*<<< orphan*/  ts_slptime; int /*<<< orphan*/  ts_ftick; int /*<<< orphan*/  ts_ltick; int /*<<< orphan*/  ts_ticks; scalar_t__ ts_flags; int /*<<< orphan*/  ts_cpu; } ;
struct TYPE_5__ {int /*<<< orphan*/  cs_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 void* NOCPU ; 
 int /*<<< orphan*/  TDQ_LOCKPTR (struct tdq*) ; 
 struct tdq* TDQ_SELF () ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* cpuset_ref (TYPE_2__*) ; 
 scalar_t__ sched_slice_min ; 
 struct td_sched* td_get_sched (struct thread*) ; 
 scalar_t__ tdq_slice (struct tdq*) ; 

void
sched_fork_thread(struct thread *td, struct thread *child)
{
	struct td_sched *ts;
	struct td_sched *ts2;
	struct tdq *tdq;

	tdq = TDQ_SELF();
	THREAD_LOCK_ASSERT(td, MA_OWNED);
	/*
	 * Initialize child.
	 */
	ts = td_get_sched(td);
	ts2 = td_get_sched(child);
	child->td_oncpu = NOCPU;
	child->td_lastcpu = NOCPU;
	child->td_lock = TDQ_LOCKPTR(tdq);
	child->td_cpuset = cpuset_ref(td->td_cpuset);
	child->td_domain.dr_policy = td->td_cpuset->cs_domain;
	ts2->ts_cpu = ts->ts_cpu;
	ts2->ts_flags = 0;
	/*
	 * Grab our parents cpu estimation information.
	 */
	ts2->ts_ticks = ts->ts_ticks;
	ts2->ts_ltick = ts->ts_ltick;
	ts2->ts_ftick = ts->ts_ftick;
	/*
	 * Do not inherit any borrowed priority from the parent.
	 */
	child->td_priority = child->td_base_pri;
	/*
	 * And update interactivity score.
	 */
	ts2->ts_slptime = ts->ts_slptime;
	ts2->ts_runtime = ts->ts_runtime;
	/* Attempt to quickly learn interactivity. */
	ts2->ts_slice = tdq_slice(tdq) - sched_slice_min;
#ifdef KTR
	bzero(ts2->ts_name, sizeof(ts2->ts_name));
#endif
}