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
struct thread {int td_slptick; int /*<<< orphan*/  td_flags; } ;
struct td_sched {int ts_slptime; scalar_t__ ts_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int SCHED_TICK_SHIFT ; 
 int /*<<< orphan*/  SRQ_BORING ; 
 int /*<<< orphan*/  TDF_CANSWAP ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_interact_update (struct thread*) ; 
 int /*<<< orphan*/  sched_pctcpu_update (struct td_sched*,int /*<<< orphan*/ ) ; 
 struct td_sched* td_get_sched (struct thread*) ; 
 int ticks ; 

void
sched_wakeup(struct thread *td)
{
	struct td_sched *ts;
	int slptick;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	ts = td_get_sched(td);
	td->td_flags &= ~TDF_CANSWAP;
	/*
	 * If we slept for more than a tick update our interactivity and
	 * priority.
	 */
	slptick = td->td_slptick;
	td->td_slptick = 0;
	if (slptick && slptick != ticks) {
		ts->ts_slptime += (ticks - slptick) << SCHED_TICK_SHIFT;
		sched_interact_update(td);
		sched_pctcpu_update(ts, 0);
	}
	/*
	 * Reset the slice value since we slept and advanced the round-robin.
	 */
	ts->ts_slice = 0;
	sched_add(td, SRQ_BORING);
}