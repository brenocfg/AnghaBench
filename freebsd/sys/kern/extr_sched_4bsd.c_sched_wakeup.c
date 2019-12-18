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
struct thread {scalar_t__ td_slptick; int /*<<< orphan*/  td_flags; } ;
struct td_sched {int ts_slptime; int /*<<< orphan*/  ts_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SRQ_BORING ; 
 int /*<<< orphan*/  TDF_CANSWAP ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetpriority (struct thread*) ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_slice ; 
 struct td_sched* td_get_sched (struct thread*) ; 
 int /*<<< orphan*/  updatepri (struct thread*) ; 

void
sched_wakeup(struct thread *td)
{
	struct td_sched *ts;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	ts = td_get_sched(td);
	td->td_flags &= ~TDF_CANSWAP;
	if (ts->ts_slptime > 1) {
		updatepri(td);
		resetpriority(td);
	}
	td->td_slptick = 0;
	ts->ts_slptime = 0;
	ts->ts_slice = sched_slice;
	sched_add(td, SRQ_BORING);
}