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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; int /*<<< orphan*/  ic_oerrors; } ;
struct iwi_softc {scalar_t__ sc_tx_timer; scalar_t__ sc_state_timer; scalar_t__ fw_state; scalar_t__ sc_busy_timer; int /*<<< orphan*/  sc_wdtimer; int /*<<< orphan*/  sc_restarttask; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ IWI_FW_SCANNING ; 
 int /*<<< orphan*/  IWI_LOCK_ASSERT (struct iwi_softc*) ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct iwi_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_cancel_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwi_watchdog(void *arg)
{
	struct iwi_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	IWI_LOCK_ASSERT(sc);

	if (sc->sc_tx_timer > 0) {
		if (--sc->sc_tx_timer == 0) {
			device_printf(sc->sc_dev, "device timeout\n");
			counter_u64_add(ic->ic_oerrors, 1);
			ieee80211_runtask(ic, &sc->sc_restarttask);
		}
	}
	if (sc->sc_state_timer > 0) {
		if (--sc->sc_state_timer == 0) {
			device_printf(sc->sc_dev,
			    "firmware stuck in state %d, resetting\n",
			    sc->fw_state);
			if (sc->fw_state == IWI_FW_SCANNING)
				ieee80211_cancel_scan(TAILQ_FIRST(&ic->ic_vaps));
			ieee80211_runtask(ic, &sc->sc_restarttask);
			sc->sc_state_timer = 3;
		}
	}
	if (sc->sc_busy_timer > 0) {
		if (--sc->sc_busy_timer == 0) {
			device_printf(sc->sc_dev,
			    "firmware command timeout, resetting\n");
			ieee80211_runtask(ic, &sc->sc_restarttask);
		}
	}
	callout_reset(&sc->sc_wdtimer, hz, iwi_watchdog, sc);
}