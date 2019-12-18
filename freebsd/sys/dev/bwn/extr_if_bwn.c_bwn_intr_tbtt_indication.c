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
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct bwn_softc {struct ieee80211com sc_ic; } ;
struct bwn_mac {int /*<<< orphan*/  mac_flags; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_MAC_FLAG_DFQVALID ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  bwn_psctl (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_intr_tbtt_indication(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;

	if (ic->ic_opmode != IEEE80211_M_HOSTAP)
		bwn_psctl(mac, 0);
	if (ic->ic_opmode == IEEE80211_M_IBSS)
		mac->mac_flags |= BWN_MAC_FLAG_DFQVALID;
}