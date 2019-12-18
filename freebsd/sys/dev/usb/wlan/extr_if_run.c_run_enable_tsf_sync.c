#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ieee80211com {scalar_t__ ic_opmode; int /*<<< orphan*/  ic_vaps; } ;
struct run_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {TYPE_1__* iv_bss; } ;
struct TYPE_4__ {int /*<<< orphan*/  rvp_id; } ;
struct TYPE_3__ {int ni_intval; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  RT2860_BCN_TIME_CFG ; 
 int RT2860_BCN_TX_EN ; 
 int RT2860_TBTT_TIMER_EN ; 
 int RT2860_TSF_SYNC_MODE_SHIFT ; 
 int RT2860_TSF_TIMER_EN ; 
 int /*<<< orphan*/  RUN_DEBUG_BEACON ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* RUN_VAP (struct ieee80211vap*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_enable_tsf_sync(struct run_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	uint32_t tmp;

	RUN_DPRINTF(sc, RUN_DEBUG_BEACON, "rvp_id=%d ic_opmode=%d\n",
	    RUN_VAP(vap)->rvp_id, ic->ic_opmode);

	run_read(sc, RT2860_BCN_TIME_CFG, &tmp);
	tmp &= ~0x1fffff;
	tmp |= vap->iv_bss->ni_intval * 16;
	tmp |= RT2860_TSF_TIMER_EN | RT2860_TBTT_TIMER_EN;

	if (ic->ic_opmode == IEEE80211_M_STA) {
		/*
		 * Local TSF is always updated with remote TSF on beacon
		 * reception.
		 */
		tmp |= 1 << RT2860_TSF_SYNC_MODE_SHIFT;
	} else if (ic->ic_opmode == IEEE80211_M_IBSS) {
	        tmp |= RT2860_BCN_TX_EN;
	        /*
	         * Local TSF is updated with remote TSF on beacon reception
	         * only if the remote TSF is greater than local TSF.
	         */
	        tmp |= 2 << RT2860_TSF_SYNC_MODE_SHIFT;
	} else if (ic->ic_opmode == IEEE80211_M_HOSTAP ||
		    ic->ic_opmode == IEEE80211_M_MBSS) {
	        tmp |= RT2860_BCN_TX_EN;
	        /* SYNC with nobody */
	        tmp |= 3 << RT2860_TSF_SYNC_MODE_SHIFT;
	} else {
		RUN_DPRINTF(sc, RUN_DEBUG_BEACON,
		    "Enabling TSF failed. undefined opmode\n");
		return;
	}

	run_write(sc, RT2860_BCN_TIME_CFG, tmp);
}