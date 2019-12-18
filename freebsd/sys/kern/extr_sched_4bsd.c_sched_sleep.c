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
struct thread {int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_pri_class; int /*<<< orphan*/  td_slptick; } ;
struct TYPE_2__ {scalar_t__ ts_slptime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PRI_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ PRI_TIMESHARE ; 
 int PSOCK ; 
 int /*<<< orphan*/  TDF_CANSWAP ; 
 scalar_t__ TD_IS_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int) ; 
 TYPE_1__* td_get_sched (struct thread*) ; 
 int /*<<< orphan*/  ticks ; 

void
sched_sleep(struct thread *td, int pri)
{

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	td->td_slptick = ticks;
	td_get_sched(td)->ts_slptime = 0;
	if (pri != 0 && PRI_BASE(td->td_pri_class) == PRI_TIMESHARE)
		sched_prio(td, pri);
	if (TD_IS_SUSPENDED(td) || pri >= PSOCK)
		td->td_flags |= TDF_CANSWAP;
}