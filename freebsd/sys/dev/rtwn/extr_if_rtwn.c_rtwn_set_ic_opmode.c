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
struct ieee80211com {int /*<<< orphan*/  ic_opmode; } ;
struct rtwn_softc {scalar_t__ bcn_vaps; scalar_t__ ap_vaps; scalar_t__ nvaps; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_M_HOSTAP ; 
 int /*<<< orphan*/  IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 

__attribute__((used)) static void
rtwn_set_ic_opmode(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	RTWN_ASSERT_LOCKED(sc);

	/* for ieee80211_reset_erp() */
	if (sc->bcn_vaps - sc->ap_vaps > 0)
		ic->ic_opmode = IEEE80211_M_IBSS;
	else if (sc->ap_vaps > 0)
		ic->ic_opmode = IEEE80211_M_HOSTAP;
	else if (sc->nvaps > 0)
		ic->ic_opmode = IEEE80211_M_STA;
	else
		ic->ic_opmode = IEEE80211_M_MONITOR;
}