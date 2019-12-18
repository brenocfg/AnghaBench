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
typedef  int uint32_t ;
struct rt2661_vap {int (* ral_newstate ) (struct ieee80211vap*,int,int) ;} ;
struct rt2661_softc {int dummy; } ;
struct ieee80211vap {scalar_t__ iv_state; scalar_t__ iv_opmode; struct ieee80211_node* iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct rt2661_softc* ic_softc; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_bssid; int /*<<< orphan*/  ni_rates; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 int IEEE80211_S_INIT ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2661_TXRX_CSR9 ; 
 struct rt2661_vap* RT2661_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  rt2661_enable_mrr (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_enable_tsf (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_enable_tsf_sync (struct rt2661_softc*) ; 
 int rt2661_prepare_beacon (struct rt2661_softc*,struct ieee80211vap*) ; 
 int /*<<< orphan*/  rt2661_set_basicrates (struct rt2661_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_set_bssid (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2661_set_txpreamble (struct rt2661_softc*) ; 
 int stub1 (struct ieee80211vap*,int,int) ; 

__attribute__((used)) static int
rt2661_newstate(struct ieee80211vap *vap, enum ieee80211_state nstate, int arg)
{
	struct rt2661_vap *rvp = RT2661_VAP(vap);
	struct ieee80211com *ic = vap->iv_ic;
	struct rt2661_softc *sc = ic->ic_softc;
	int error;

	if (nstate == IEEE80211_S_INIT && vap->iv_state == IEEE80211_S_RUN) {
		uint32_t tmp;

		/* abort TSF synchronization */
		tmp = RAL_READ(sc, RT2661_TXRX_CSR9);
		RAL_WRITE(sc, RT2661_TXRX_CSR9, tmp & ~0x00ffffff);
	}

	error = rvp->ral_newstate(vap, nstate, arg);

	if (error == 0 && nstate == IEEE80211_S_RUN) {
		struct ieee80211_node *ni = vap->iv_bss;

		if (vap->iv_opmode != IEEE80211_M_MONITOR) {
			rt2661_enable_mrr(sc);
			rt2661_set_txpreamble(sc);
			rt2661_set_basicrates(sc, &ni->ni_rates);
			rt2661_set_bssid(sc, ni->ni_bssid);
		}

		if (vap->iv_opmode == IEEE80211_M_HOSTAP ||
		    vap->iv_opmode == IEEE80211_M_IBSS ||
		    vap->iv_opmode == IEEE80211_M_MBSS) {
			error = rt2661_prepare_beacon(sc, vap);
			if (error != 0)
				return error;
		}
		if (vap->iv_opmode != IEEE80211_M_MONITOR)
			rt2661_enable_tsf_sync(sc);
		else
			rt2661_enable_tsf(sc);
	}
	return error;
}