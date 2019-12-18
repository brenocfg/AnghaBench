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
struct upgt_vap {int (* newstate ) (struct ieee80211vap*,int,int) ;} ;
struct upgt_softc {int sc_state; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_led_ch; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; struct upgt_softc* ic_softc; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
#define  IEEE80211_S_ASSOC 132 
#define  IEEE80211_S_AUTH 131 
#define  IEEE80211_S_INIT 130 
#define  IEEE80211_S_RUN 129 
#define  IEEE80211_S_SCAN 128 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  UPGT_LED_OFF ; 
 int /*<<< orphan*/  UPGT_LED_ON ; 
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 struct upgt_vap* UPGT_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int stub1 (struct ieee80211vap*,int,int) ; 
 int /*<<< orphan*/  upgt_set_chan (struct upgt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upgt_set_led (struct upgt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upgt_set_macfilter (struct upgt_softc*,int) ; 

__attribute__((used)) static int
upgt_newstate(struct ieee80211vap *vap, enum ieee80211_state nstate, int arg)
{
	struct upgt_vap *uvp = UPGT_VAP(vap);
	struct ieee80211com *ic = vap->iv_ic;
	struct upgt_softc *sc = ic->ic_softc;

	/* do it in a process context */
	sc->sc_state = nstate;

	IEEE80211_UNLOCK(ic);
	UPGT_LOCK(sc);
	callout_stop(&sc->sc_led_ch);
	callout_stop(&sc->sc_watchdog_ch);

	switch (nstate) {
	case IEEE80211_S_INIT:
		/* do not accept any frames if the device is down */
		(void)upgt_set_macfilter(sc, sc->sc_state);
		upgt_set_led(sc, UPGT_LED_OFF);
		break;
	case IEEE80211_S_SCAN:
		upgt_set_chan(sc, ic->ic_curchan);
		break;
	case IEEE80211_S_AUTH:
		upgt_set_chan(sc, ic->ic_curchan);
		break;
	case IEEE80211_S_ASSOC:
		break;
	case IEEE80211_S_RUN:
		upgt_set_macfilter(sc, sc->sc_state);
		upgt_set_led(sc, UPGT_LED_ON);
		break;
	default:
		break;
	}
	UPGT_UNLOCK(sc);
	IEEE80211_LOCK(ic);
	return (uvp->newstate(vap, nstate, arg));
}