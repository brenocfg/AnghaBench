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
struct ieee80211_channel {int dummy; } ;
struct ath_softc {int sc_curmode; struct ieee80211_channel* sc_curchan; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 int /*<<< orphan*/  ath_setcurmode (struct ath_softc*,int) ; 
 int ieee80211_chan2mode (struct ieee80211_channel*) ; 

__attribute__((used)) static void
ath_chan_change(struct ath_softc *sc, struct ieee80211_channel *chan)
{
	enum ieee80211_phymode mode;

	/*
	 * Change channels and update the h/w rate map
	 * if we're switching; e.g. 11a to 11b/g.
	 */
	mode = ieee80211_chan2mode(chan);
	if (mode != sc->sc_curmode)
		ath_setcurmode(sc, mode);
	sc->sc_curchan = chan;
}