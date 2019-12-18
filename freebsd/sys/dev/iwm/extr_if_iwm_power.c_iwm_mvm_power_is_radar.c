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
struct ieee80211com {struct ieee80211_channel* ic_bsschan; } ;
struct iwm_softc {struct ieee80211com sc_ic; } ;
struct ieee80211_channel {int ic_flags; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct ieee80211_channel* IEEE80211_CHAN_ANYC ; 
 int IEEE80211_CHAN_DFS ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
iwm_mvm_power_is_radar(struct iwm_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211_channel *chan;
	boolean_t radar_detect = FALSE;

	chan = ic->ic_bsschan;
	if (chan == IEEE80211_CHAN_ANYC ||
	    (chan->ic_flags & IEEE80211_CHAN_DFS) != 0) {
		radar_detect = TRUE;
	}

        return radar_detect;
}