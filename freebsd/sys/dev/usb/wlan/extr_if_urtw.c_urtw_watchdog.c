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
struct ieee80211com {int /*<<< orphan*/  ic_oerrors; } ;
struct urtw_softc {scalar_t__ sc_txtimer; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct urtw_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_restart_all (struct ieee80211com*) ; 

__attribute__((used)) static void
urtw_watchdog(void *arg)
{
	struct urtw_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	if (sc->sc_txtimer > 0) {
		if (--sc->sc_txtimer == 0) {
			device_printf(sc->sc_dev, "device timeout\n");
			counter_u64_add(ic->ic_oerrors, 1);
			ieee80211_restart_all(ic);
			return;
		}
		callout_reset(&sc->sc_watchdog_ch, hz, urtw_watchdog, sc);
	}
}