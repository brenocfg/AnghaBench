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
struct rl_softc {int rl_flags; scalar_t__ rl_twister; int /*<<< orphan*/  rl_stat_callout; scalar_t__ rl_twister_enable; int /*<<< orphan*/  rl_dev; int /*<<< orphan*/  rl_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ DONE ; 
 int RL_FLAG_LINK ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct rl_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  rl_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_twister_update (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_watchdog (struct rl_softc*) ; 

__attribute__((used)) static void
rl_tick(void *xsc)
{
	struct rl_softc		*sc = xsc;
	struct mii_data		*mii;
	int ticks;

	RL_LOCK_ASSERT(sc);
	/*
	 * If we're doing the twister cable calibration, then we need to defer
	 * watchdog timeouts.  This is a no-op in normal operations, but
	 * can falsely trigger when the cable calibration takes a while and
	 * there was traffic ready to go when rl was started.
	 *
	 * We don't defer mii_tick since that updates the mii status, which
	 * helps the twister process, at least according to similar patches
	 * for the Linux driver I found online while doing the fixes.  Worst
	 * case is a few extra mii reads during calibration.
	 */
	mii = device_get_softc(sc->rl_miibus);
	mii_tick(mii);
	if ((sc->rl_flags & RL_FLAG_LINK) == 0)
		rl_miibus_statchg(sc->rl_dev);
	if (sc->rl_twister_enable) {
		if (sc->rl_twister == DONE)
			rl_watchdog(sc);
		else
			rl_twister_update(sc);
		if (sc->rl_twister == DONE)
			ticks = hz;
		else
			ticks = hz / 10;
	} else {
		rl_watchdog(sc);
		ticks = hz;
	}

	callout_reset(&sc->rl_stat_callout, ticks, rl_tick, sc);
}