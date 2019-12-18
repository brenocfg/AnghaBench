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
struct thread {int dummy; } ;
struct td_sched {scalar_t__ ts_ticks; } ;
typedef  int fixpt_t ;

/* Variables and functions */
 int FSCALE ; 
 int FSHIFT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SCHED_TICK_HZ (struct td_sched*) ; 
 int SCHED_TICK_SECS ; 
 int /*<<< orphan*/  TD_IS_RUNNING (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int min (int,int) ; 
 int /*<<< orphan*/  sched_pctcpu_update (struct td_sched*,int /*<<< orphan*/ ) ; 
 struct td_sched* td_get_sched (struct thread*) ; 

fixpt_t
sched_pctcpu(struct thread *td)
{
	fixpt_t pctcpu;
	struct td_sched *ts;

	pctcpu = 0;
	ts = td_get_sched(td);

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	sched_pctcpu_update(ts, TD_IS_RUNNING(td));
	if (ts->ts_ticks) {
		int rtick;

		/* How many rtick per second ? */
		rtick = min(SCHED_TICK_HZ(ts) / SCHED_TICK_SECS, hz);
		pctcpu = (FSCALE * ((FSCALE * rtick)/hz)) >> FSHIFT;
	}

	return (pctcpu);
}