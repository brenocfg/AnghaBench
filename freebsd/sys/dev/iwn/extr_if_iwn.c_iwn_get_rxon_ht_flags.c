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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211com {int ic_curhtprotmode; } ;
struct iwn_softc {struct ieee80211com sc_ic; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
#define  IEEE80211_HTINFO_OPMODE_HT20PR 128 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HT (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40D (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IWN_RXON_HT_HT40MINUS ; 
 int /*<<< orphan*/  IWN_RXON_HT_MODEMIXED ; 
 int /*<<< orphan*/  IWN_RXON_HT_MODEPURE40 ; 
 int /*<<< orphan*/  IWN_RXON_HT_PROTMODE (int) ; 

__attribute__((used)) static uint32_t
iwn_get_rxon_ht_flags(struct iwn_softc *sc, struct ieee80211_channel *c)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t htflags = 0;

	if (! IEEE80211_IS_CHAN_HT(c))
		return (0);

	htflags |= IWN_RXON_HT_PROTMODE(ic->ic_curhtprotmode);

	if (IEEE80211_IS_CHAN_HT40(c)) {
		switch (ic->ic_curhtprotmode) {
		case IEEE80211_HTINFO_OPMODE_HT20PR:
			htflags |= IWN_RXON_HT_MODEPURE40;
			break;
		default:
			htflags |= IWN_RXON_HT_MODEMIXED;
			break;
		}
	}
	if (IEEE80211_IS_CHAN_HT40D(c))
		htflags |= IWN_RXON_HT_HT40MINUS;

	return (htflags);
}