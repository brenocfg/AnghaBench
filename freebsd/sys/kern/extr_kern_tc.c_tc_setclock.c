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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct bintime {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  atomic_add_rel_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,struct bintime*) ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 
 int /*<<< orphan*/  cpu_tick_calibrate (int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int /*<<< orphan*/  rtc_generation ; 
 int /*<<< orphan*/  sleeping_on_old_rtc ; 
 int /*<<< orphan*/  sleepq_chains_remove_matching (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_setclock_mtx ; 
 int /*<<< orphan*/  tc_windup (struct bintime*) ; 
 int /*<<< orphan*/  timespec2bintime (struct timespec*,struct bintime*) ; 
 scalar_t__ timestepwarnings ; 

void
tc_setclock(struct timespec *ts)
{
	struct timespec tbef, taft;
	struct bintime bt, bt2;

	timespec2bintime(ts, &bt);
	nanotime(&tbef);
	mtx_lock_spin(&tc_setclock_mtx);
	cpu_tick_calibrate(1);
	binuptime(&bt2);
	bintime_sub(&bt, &bt2);

	/* XXX fiddle all the little crinkly bits around the fiords... */
	tc_windup(&bt);
	mtx_unlock_spin(&tc_setclock_mtx);

	/* Avoid rtc_generation == 0, since td_rtcgen == 0 is special. */
	atomic_add_rel_int(&rtc_generation, 2);
	sleepq_chains_remove_matching(sleeping_on_old_rtc);
	if (timestepwarnings) {
		nanotime(&taft);
		log(LOG_INFO,
		    "Time stepped from %jd.%09ld to %jd.%09ld (%jd.%09ld)\n",
		    (intmax_t)tbef.tv_sec, tbef.tv_nsec,
		    (intmax_t)taft.tv_sec, taft.tv_nsec,
		    (intmax_t)ts->tv_sec, ts->tv_nsec);
	}
}