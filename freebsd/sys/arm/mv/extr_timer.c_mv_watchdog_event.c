#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  timer_mtx; TYPE_1__* config; } ;
struct TYPE_3__ {unsigned int clock_src; int /*<<< orphan*/  (* watchdog_enable ) () ;int /*<<< orphan*/  (* watchdog_disable ) () ;} ;

/* Variables and functions */
 unsigned int MAX_WATCHDOG_TICKS ; 
 int /*<<< orphan*/  WATCHDOG_TIMER_ARMV5 ; 
 unsigned int WD_INTERVAL ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_set_timer (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 TYPE_2__* timer_softc ; 

__attribute__((used)) static void
mv_watchdog_event(void *arg, unsigned int cmd, int *error)
{
	uint64_t ns;
	uint64_t ticks;

	mtx_lock(&timer_softc->timer_mtx);
	if (cmd == 0) {
		if (timer_softc->config->watchdog_disable != NULL)
			timer_softc->config->watchdog_disable();
	} else {
		/*
		 * Watchdog timeout is in nanosecs, calculation according to
		 * watchdog(9)
		 */
		ns = (uint64_t)1 << (cmd & WD_INTERVAL);
		ticks = (uint64_t)(ns * timer_softc->config->clock_src) / 1000000000;
		if (ticks > MAX_WATCHDOG_TICKS) {
			if (timer_softc->config->watchdog_disable != NULL)
				timer_softc->config->watchdog_disable();
		} else {
			mv_set_timer(WATCHDOG_TIMER_ARMV5, ticks);
			if (timer_softc->config->watchdog_enable != NULL)
				timer_softc->config->watchdog_enable();
			*error = 0;
		}
	}
	mtx_unlock(&timer_softc->timer_mtx);
}