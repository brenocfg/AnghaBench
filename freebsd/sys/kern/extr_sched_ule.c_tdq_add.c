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
struct thread {scalar_t__ td_inhibitors; int td_flags; scalar_t__ td_priority; } ;
struct tdq {scalar_t__ tdq_lowpri; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int TDF_INMEM ; 
 int /*<<< orphan*/  TDQ_LOCK_ASSERT (struct tdq*,int /*<<< orphan*/ ) ; 
 scalar_t__ TD_CAN_RUN (struct thread*) ; 
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 int /*<<< orphan*/  tdq_load_add (struct tdq*,struct thread*) ; 
 int /*<<< orphan*/  tdq_runq_add (struct tdq*,struct thread*,int) ; 

void
tdq_add(struct tdq *tdq, struct thread *td, int flags)
{

	TDQ_LOCK_ASSERT(tdq, MA_OWNED);
	KASSERT((td->td_inhibitors == 0),
	    ("sched_add: trying to run inhibited thread"));
	KASSERT((TD_CAN_RUN(td) || TD_IS_RUNNING(td)),
	    ("sched_add: bad thread state"));
	KASSERT(td->td_flags & TDF_INMEM,
	    ("sched_add: thread swapped out"));

	if (td->td_priority < tdq->tdq_lowpri)
		tdq->tdq_lowpri = td->td_priority;
	tdq_runq_add(tdq, td, flags);
	tdq_load_add(tdq, td);
}