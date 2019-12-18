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
struct thread {int td_priority; int /*<<< orphan*/  td_pri_class; int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_slptick; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PRI_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ PRI_TIMESHARE ; 
 int PSOCK ; 
 int /*<<< orphan*/  TDF_CANSWAP ; 
 scalar_t__ TD_IS_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int) ; 
 int static_boost ; 
 int /*<<< orphan*/  ticks ; 

void
sched_sleep(struct thread *td, int prio)
{

	THREAD_LOCK_ASSERT(td, MA_OWNED);

	td->td_slptick = ticks;
	if (TD_IS_SUSPENDED(td) || prio >= PSOCK)
		td->td_flags |= TDF_CANSWAP;
	if (PRI_BASE(td->td_pri_class) != PRI_TIMESHARE)
		return;
	if (static_boost == 1 && prio)
		sched_prio(td, prio);
	else if (static_boost && td->td_priority > static_boost)
		sched_prio(td, static_boost);
}