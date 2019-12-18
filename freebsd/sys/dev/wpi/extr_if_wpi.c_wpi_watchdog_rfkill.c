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
struct ieee80211com {int dummy; } ;
struct wpi_softc {int /*<<< orphan*/  sc_radioon_task; int /*<<< orphan*/  watchdog_rfkill; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct wpi_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WPI_APMG_RFKILL ; 
 int /*<<< orphan*/  WPI_DEBUG_WATCHDOG ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct wpi_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int wpi_prph_read (struct wpi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wpi_watchdog_rfkill(void *arg)
{
	struct wpi_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	DPRINTF(sc, WPI_DEBUG_WATCHDOG, "RFkill Watchdog: tick\n");

	/* No need to lock firmware memory. */
	if ((wpi_prph_read(sc, WPI_APMG_RFKILL) & 0x1) == 0) {
		/* Radio kill switch is still off. */
		callout_reset(&sc->watchdog_rfkill, hz, wpi_watchdog_rfkill,
		    sc);
	} else
		ieee80211_runtask(ic, &sc->sc_radioon_task);
}