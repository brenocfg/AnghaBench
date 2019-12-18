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
typedef  int uint8_t ;
struct ieee80211com {scalar_t__ ic_curmode; } ;
struct upgt_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MODE_11B ; 
 scalar_t__ IEEE80211_MODE_11G ; 

__attribute__((used)) static uint8_t
upgt_rx_rate(struct upgt_softc *sc, const int rate)
{
	struct ieee80211com *ic = &sc->sc_ic;
	static const uint8_t cck_upgt2rate[4] = { 2, 4, 11, 22 };
	static const uint8_t ofdm_upgt2rate[12] =
	    { 2, 4, 11, 22, 12, 18, 24, 36, 48, 72, 96, 108 };
	
	if (ic->ic_curmode == IEEE80211_MODE_11B &&
	    !(rate < 0 || rate > 3))
		return cck_upgt2rate[rate & 0xf];

	if (ic->ic_curmode == IEEE80211_MODE_11G &&
	    !(rate < 0 || rate > 11))
		return ofdm_upgt2rate[rate & 0xf];

	return (0);
}