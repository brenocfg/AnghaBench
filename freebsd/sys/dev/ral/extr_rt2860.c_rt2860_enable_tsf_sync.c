#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct rt2860_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {scalar_t__ iv_opmode; TYPE_1__* iv_bss; } ;
struct TYPE_2__ {int ni_intval; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 scalar_t__ IEEE80211_M_STA ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2860_BCN_TIME_CFG ; 
 int RT2860_BCN_TX_EN ; 
 int RT2860_TBTT_TIMER_EN ; 
 int RT2860_TSF_SYNC_MODE_SHIFT ; 
 int RT2860_TSF_TIMER_EN ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt2860_enable_tsf_sync(struct rt2860_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	uint32_t tmp;

	tmp = RAL_READ(sc, RT2860_BCN_TIME_CFG);

	tmp &= ~0x1fffff;
	tmp |= vap->iv_bss->ni_intval * 16;
	tmp |= RT2860_TSF_TIMER_EN | RT2860_TBTT_TIMER_EN;
	if (vap->iv_opmode == IEEE80211_M_STA) {
		/*
		 * Local TSF is always updated with remote TSF on beacon
		 * reception.
		 */
		tmp |= 1 << RT2860_TSF_SYNC_MODE_SHIFT;
	}
	else if (vap->iv_opmode == IEEE80211_M_IBSS ||
	    vap->iv_opmode == IEEE80211_M_MBSS) {
		tmp |= RT2860_BCN_TX_EN;
		/*
		 * Local TSF is updated with remote TSF on beacon reception
		 * only if the remote TSF is greater than local TSF.
		 */
		tmp |= 2 << RT2860_TSF_SYNC_MODE_SHIFT;
	} else if (vap->iv_opmode == IEEE80211_M_HOSTAP) {
		tmp |= RT2860_BCN_TX_EN;
		/* SYNC with nobody */
		tmp |= 3 << RT2860_TSF_SYNC_MODE_SHIFT;
	}

	RAL_WRITE(sc, RT2860_BCN_TIME_CFG, tmp);
}