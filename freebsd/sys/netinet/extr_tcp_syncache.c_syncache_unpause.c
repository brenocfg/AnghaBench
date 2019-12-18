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
typedef  scalar_t__ time_t ;
struct tcp_syncache {scalar_t__ pause_until; int paused; int /*<<< orphan*/  pause_co; int /*<<< orphan*/  pause_mtx; } ;

/* Variables and functions */
 int MA_NOTRECURSED ; 
 int MA_OWNED ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hz ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
syncache_unpause(void *arg)
{
	struct tcp_syncache *sc;
	time_t delta;

	sc = arg;
	mtx_assert(&sc->pause_mtx, MA_OWNED | MA_NOTRECURSED);
	callout_deactivate(&sc->pause_co);

	/*
	 * Check to make sure we are not running early. If the pause
	 * time has expired, then deactivate the protection.
	 */
	if ((delta = sc->pause_until - time_uptime) > 0)
		callout_schedule(&sc->pause_co, delta * hz);
	else
		sc->paused = false;
}