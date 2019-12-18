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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct wpi_softc {int /*<<< orphan*/  watchdog_rfkill; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPI_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_notify_radio (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop (struct ieee80211vap*) ; 
 int /*<<< orphan*/  wpi_stop (struct wpi_softc*) ; 
 int /*<<< orphan*/  wpi_watchdog_rfkill ; 

__attribute__((used)) static void
wpi_radio_off(void *arg0, int pending)
{
	struct wpi_softc *sc = arg0;
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	device_printf(sc->sc_dev, "RF switch: radio disabled\n");

	ieee80211_notify_radio(ic, 0);
	wpi_stop(sc);
	if (vap != NULL)
		ieee80211_stop(vap);

	WPI_LOCK(sc);
	callout_reset(&sc->watchdog_rfkill, hz, wpi_watchdog_rfkill, sc);
	WPI_UNLOCK(sc);
}