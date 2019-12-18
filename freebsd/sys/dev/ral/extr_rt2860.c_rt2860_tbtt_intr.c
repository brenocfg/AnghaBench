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
struct ieee80211com {scalar_t__ ic_opmode; scalar_t__ ic_dtim_count; scalar_t__ ic_dtim_period; int ic_flags; } ;
struct rt2860_softc {int sc_ic_flags; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_F_USEPROT ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 int /*<<< orphan*/  ieee80211_notify_dtim (struct ieee80211com*) ; 
 int /*<<< orphan*/  rt2860_setup_beacon (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_updateprot (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_tbtt_intr(struct rt2860_softc *sc)
{
#if 0
	struct ieee80211com *ic = &sc->sc_ic;

#ifndef IEEE80211_STA_ONLY
	if (ic->ic_opmode == IEEE80211_M_HOSTAP) {
		/* one less beacon until next DTIM */
		if (ic->ic_dtim_count == 0)
			ic->ic_dtim_count = ic->ic_dtim_period - 1;
		else
			ic->ic_dtim_count--;

		/* update dynamic parts of beacon */
		rt2860_setup_beacon(sc);

		/* flush buffered multicast frames */
		if (ic->ic_dtim_count == 0)
			ieee80211_notify_dtim(ic);
	}
#endif
	/* check if protection mode has changed */
	if ((sc->sc_ic_flags ^ ic->ic_flags) & IEEE80211_F_USEPROT) {
		rt2860_updateprot(sc);
		sc->sc_ic_flags = ic->ic_flags;
	}
#endif
}