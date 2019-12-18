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
struct iwn_softc {int sc_flags; int /*<<< orphan*/  calib_to; int /*<<< orphan*/  scan_timeout; int /*<<< orphan*/  watchdog_to; scalar_t__ sc_tx_timer; scalar_t__ sc_is_scanning; } ;

/* Variables and functions */
 int IWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  IWN_LOCK_ASSERT (struct iwn_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwn_hw_stop (struct iwn_softc*) ; 

__attribute__((used)) static void
iwn_stop_locked(struct iwn_softc *sc)
{

	IWN_LOCK_ASSERT(sc);

	if (!(sc->sc_flags & IWN_FLAG_RUNNING))
		return;

	sc->sc_is_scanning = 0;
	sc->sc_tx_timer = 0;
	callout_stop(&sc->watchdog_to);
	callout_stop(&sc->scan_timeout);
	callout_stop(&sc->calib_to);
	sc->sc_flags &= ~IWN_FLAG_RUNNING;

	/* Power OFF hardware. */
	iwn_hw_stop(sc);
}