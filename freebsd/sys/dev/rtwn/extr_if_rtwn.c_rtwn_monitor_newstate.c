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
struct rtwn_vap {int (* newstate ) (struct ieee80211vap*,int,int) ;} ;
struct rtwn_softc {int vaps_running; int /*<<< orphan*/  monvaps_running; } ;
struct ieee80211vap {size_t iv_state; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct rtwn_softc* ic_softc; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
#define  IEEE80211_S_INIT 129 
#define  IEEE80211_S_RUN 128 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  RTWN_DEBUG_STATE ; 
 int /*<<< orphan*/  RTWN_DPRINTF (struct rtwn_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTWN_LED_LINK ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/ * ieee80211_state_name ; 
 int /*<<< orphan*/  rtwn_set_led (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ieee80211vap*,int,int) ; 

__attribute__((used)) static int
rtwn_monitor_newstate(struct ieee80211vap *vap, enum ieee80211_state nstate,
    int arg)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct rtwn_softc *sc = ic->ic_softc;
	struct rtwn_vap *uvp = RTWN_VAP(vap);

	RTWN_DPRINTF(sc, RTWN_DEBUG_STATE, "%s -> %s\n",
	    ieee80211_state_name[vap->iv_state],
	    ieee80211_state_name[nstate]);

	if (vap->iv_state != nstate) {
		IEEE80211_UNLOCK(ic);
		RTWN_LOCK(sc);

		switch (nstate) {
		case IEEE80211_S_INIT:
			sc->vaps_running--;
			sc->monvaps_running--;

			if (sc->vaps_running == 0) {
				/* Turn link LED off. */
				rtwn_set_led(sc, RTWN_LED_LINK, 0);
			}
			break;
		case IEEE80211_S_RUN:
			sc->vaps_running++;
			sc->monvaps_running++;

			if (sc->vaps_running == 1) {
				/* Turn link LED on. */
				rtwn_set_led(sc, RTWN_LED_LINK, 1);
			}
			break;
		default:
			/* NOTREACHED */
			break;
		}

		RTWN_UNLOCK(sc);
		IEEE80211_LOCK(ic);
	}

	return (uvp->newstate(vap, nstate, arg));
}