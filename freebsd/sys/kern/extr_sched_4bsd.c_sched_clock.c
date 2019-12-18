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
struct thread {int td_flags; } ;
struct td_sched {int ts_estcpu; scalar_t__ ts_slice; int /*<<< orphan*/  ts_cpticks; } ;
struct pcpuidlestat {scalar_t__ idlecalls; scalar_t__ oldidlecalls; } ;

/* Variables and functions */
 struct pcpuidlestat* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int ESTCPULIM (int) ; 
 int INVERSE_ESTCPU_WEIGHT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int TDF_NEEDRESCHED ; 
 int TDF_SLICEEND ; 
 int /*<<< orphan*/  TD_IS_IDLETHREAD (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idlestat ; 
 int /*<<< orphan*/  resetpriority (struct thread*) ; 
 int /*<<< orphan*/  resetpriority_thread (struct thread*) ; 
 scalar_t__ sched_slice ; 
 struct td_sched* td_get_sched (struct thread*) ; 

void
sched_clock(struct thread *td)
{
	struct pcpuidlestat *stat;
	struct td_sched *ts;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	ts = td_get_sched(td);

	ts->ts_cpticks++;
	ts->ts_estcpu = ESTCPULIM(ts->ts_estcpu + 1);
	if ((ts->ts_estcpu % INVERSE_ESTCPU_WEIGHT) == 0) {
		resetpriority(td);
		resetpriority_thread(td);
	}

	/*
	 * Force a context switch if the current thread has used up a full
	 * time slice (default is 100ms).
	 */
	if (!TD_IS_IDLETHREAD(td) && --ts->ts_slice <= 0) {
		ts->ts_slice = sched_slice;
		td->td_flags |= TDF_NEEDRESCHED | TDF_SLICEEND;
	}

	stat = DPCPU_PTR(idlestat);
	stat->oldidlecalls = stat->idlecalls;
	stat->idlecalls = 0;
}