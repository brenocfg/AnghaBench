#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_4__ {int /*<<< orphan*/  (* tc_get_timecount ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ2BT (int,int /*<<< orphan*/ *) ; 
 void* bttosbt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffclock_init () ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  tc_adjprecision () ; 
 int /*<<< orphan*/  tc_setclock_mtx ; 
 int tc_tick ; 
 int /*<<< orphan*/  tc_tick_bt ; 
 void* tc_tick_sbt ; 
 int /*<<< orphan*/  tc_windup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_bt ; 
 void* tick_sbt ; 
 TYPE_1__* timecounter ; 

__attribute__((used)) static void
inittimecounter(void *dummy)
{
	u_int p;
	int tick_rate;

	/*
	 * Set the initial timeout to
	 * max(1, <approx. number of hardclock ticks in a millisecond>).
	 * People should probably not use the sysctl to set the timeout
	 * to smaller than its initial value, since that value is the
	 * smallest reasonable one.  If they want better timestamps they
	 * should use the non-"get"* functions.
	 */
	if (hz > 1000)
		tc_tick = (hz + 500) / 1000;
	else
		tc_tick = 1;
	tc_adjprecision();
	FREQ2BT(hz, &tick_bt);
	tick_sbt = bttosbt(tick_bt);
	tick_rate = hz / tc_tick;
	FREQ2BT(tick_rate, &tc_tick_bt);
	tc_tick_sbt = bttosbt(tc_tick_bt);
	p = (tc_tick * 1000000) / hz;
	printf("Timecounters tick every %d.%03u msec\n", p / 1000, p % 1000);

#ifdef FFCLOCK
	ffclock_init();
#endif

	/* warm up new timecounter (again) and get rolling. */
	(void)timecounter->tc_get_timecount(timecounter);
	(void)timecounter->tc_get_timecount(timecounter);
	mtx_lock_spin(&tc_setclock_mtx);
	tc_windup(NULL);
	mtx_unlock_spin(&tc_setclock_mtx);
}