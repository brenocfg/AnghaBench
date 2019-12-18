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

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  WATCHDOG_THRESHOLD ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_callout ; 
 int /*<<< orphan*/  watchdog_timer ; 

__attribute__((used)) static void
watchdog_function(void *arg)
{

	/*
	 * Since the timer ran, we must not be wedged.  Acquire some critical
	 * locks to make sure.  Then reset the timer.
	 */
	mtx_lock(&Giant);
	watchdog_timer = WATCHDOG_THRESHOLD;
	mtx_unlock(&Giant);
	callout_reset(&watchdog_callout, 1 * hz, watchdog_function, NULL);
}