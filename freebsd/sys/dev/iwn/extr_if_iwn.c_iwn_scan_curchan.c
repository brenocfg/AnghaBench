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
struct iwn_softc {int dummy; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; struct iwn_softc* ic_softc; } ;
struct ieee80211_scan_state {struct ieee80211vap* ss_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  ieee80211_cancel_scan (struct ieee80211vap*) ; 
 int iwn_scan (struct iwn_softc*,struct ieee80211vap*,struct ieee80211_scan_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwn_scan_curchan(struct ieee80211_scan_state *ss, unsigned long maxdwell)
{
	struct ieee80211vap *vap = ss->ss_vap;
	struct ieee80211com *ic = vap->iv_ic;
	struct iwn_softc *sc = ic->ic_softc;
	int error;

	IWN_LOCK(sc);
	error = iwn_scan(sc, vap, ss, ic->ic_curchan);
	IWN_UNLOCK(sc);
	if (error != 0)
		ieee80211_cancel_scan(vap);
}