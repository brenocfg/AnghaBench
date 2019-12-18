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
struct ieee80211com {scalar_t__ ic_curchan; scalar_t__ ic_bsschan; struct ath_softc* ic_softc; } ;
struct ath_softc {int sc_syncbeacon; int /*<<< orphan*/  sc_scanning; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  ath_chan_set (struct ath_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath_set_channel(struct ieee80211com *ic)
{
	struct ath_softc *sc = ic->ic_softc;

	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ATH_UNLOCK(sc);

	(void) ath_chan_set(sc, ic->ic_curchan);
	/*
	 * If we are returning to our bss channel then mark state
	 * so the next recv'd beacon's tsf will be used to sync the
	 * beacon timers.  Note that since we only hear beacons in
	 * sta/ibss mode this has no effect in other operating modes.
	 */
	ATH_LOCK(sc);
	if (!sc->sc_scanning && ic->ic_curchan == ic->ic_bsschan)
		sc->sc_syncbeacon = 1;
	ath_power_restore_power_state(sc);
	ATH_UNLOCK(sc);
}