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
struct thread {scalar_t__ td_priority; } ;
struct tdq {int /*<<< orphan*/  tdq_idle; int /*<<< orphan*/  tdq_ridx; int /*<<< orphan*/  tdq_timeshare; int /*<<< orphan*/  tdq_realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PRI_MIN_BATCH ; 
 scalar_t__ PRI_MIN_IDLE ; 
 int /*<<< orphan*/  TDQ_LOCK_ASSERT (struct tdq*,int /*<<< orphan*/ ) ; 
 struct thread* runq_choose (int /*<<< orphan*/ *) ; 
 struct thread* runq_choose_from (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct thread *
tdq_choose(struct tdq *tdq)
{
	struct thread *td;

	TDQ_LOCK_ASSERT(tdq, MA_OWNED);
	td = runq_choose(&tdq->tdq_realtime);
	if (td != NULL)
		return (td);
	td = runq_choose_from(&tdq->tdq_timeshare, tdq->tdq_ridx);
	if (td != NULL) {
		KASSERT(td->td_priority >= PRI_MIN_BATCH,
		    ("tdq_choose: Invalid priority on timeshare queue %d",
		    td->td_priority));
		return (td);
	}
	td = runq_choose(&tdq->tdq_idle);
	if (td != NULL) {
		KASSERT(td->td_priority >= PRI_MIN_IDLE,
		    ("tdq_choose: Invalid priority on idle queue %d",
		    td->td_priority));
		return (td);
	}

	return (NULL);
}