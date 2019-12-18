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
struct rsu_vap {int (* newstate ) (struct ieee80211vap*,int,int) ;} ;
struct rsu_softc {int sc_vap_is_running; } ;
struct ieee80211vap {int iv_state; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct rsu_softc* ic_softc; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
#define  IEEE80211_S_INIT 129 
#define  IEEE80211_S_RUN 128 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 struct rsu_vap* RSU_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  rsu_rxfilter_refresh (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_set_led (struct rsu_softc*,int) ; 
 int stub1 (struct ieee80211vap*,int,int) ; 

__attribute__((used)) static int
rsu_monitor_newstate(struct ieee80211vap *vap, enum ieee80211_state nstate,
    int arg)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct rsu_softc *sc = ic->ic_softc;
	struct rsu_vap *uvp = RSU_VAP(vap);

	if (vap->iv_state != nstate) {
		IEEE80211_UNLOCK(ic);
		RSU_LOCK(sc);

		switch (nstate) {
		case IEEE80211_S_INIT:
			sc->sc_vap_is_running = 0;
			rsu_set_led(sc, 0);
			break;
		case IEEE80211_S_RUN:
			sc->sc_vap_is_running = 1;
			rsu_set_led(sc, 1);
			break;
		default:
			/* NOTREACHED */
			break;
		}
		rsu_rxfilter_refresh(sc);

		RSU_UNLOCK(sc);
		IEEE80211_LOCK(ic);
	}

	return (uvp->newstate(vap, nstate, arg));
}