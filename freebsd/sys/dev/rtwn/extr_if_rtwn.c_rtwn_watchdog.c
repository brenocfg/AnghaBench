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
struct rtwn_softc {int sc_flags; scalar_t__ sc_tx_timer; int /*<<< orphan*/  sc_watchdog_to; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int RTWN_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct rtwn_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*) ; 
 int /*<<< orphan*/  ieee80211_restart_all (struct ieee80211com*) ; 

__attribute__((used)) static void
rtwn_watchdog(void *arg)
{
	struct rtwn_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	RTWN_ASSERT_LOCKED(sc);

	KASSERT(sc->sc_flags & RTWN_RUNNING, ("not running"));

	if (sc->sc_tx_timer != 0 && --sc->sc_tx_timer == 0) {
		ic_printf(ic, "device timeout\n");
		ieee80211_restart_all(ic);
		return;
	}
	callout_reset(&sc->sc_watchdog_to, hz, rtwn_watchdog, sc);
}