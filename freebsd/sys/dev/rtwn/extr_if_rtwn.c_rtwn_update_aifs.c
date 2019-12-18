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
typedef  size_t uint8_t ;
struct wmeParams {size_t wmep_aifsn; } ;
struct TYPE_2__ {struct ieee80211_channel* ic_curchan; } ;
struct rtwn_softc {struct wmeParams* cap_wmeParams; TYPE_1__ sc_ic; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_DUR_OFDM_SIFS ; 
 size_t IEEE80211_DUR_SIFS ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel*) ; 
 size_t WME_AC_BE ; 
 size_t WME_NUM_AC ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * wme2reg ; 

__attribute__((used)) static void
rtwn_update_aifs(struct rtwn_softc *sc, uint8_t slottime)
{
	struct ieee80211_channel *c = sc->sc_ic.ic_curchan;
	const struct wmeParams *wmep = sc->cap_wmeParams;
	uint8_t aifs, ac;

	for (ac = WME_AC_BE; ac < WME_NUM_AC; ac++) {
		/* AIFS[AC] = AIFSN[AC] * aSlotTime + aSIFSTime. */
		aifs = wmep[ac].wmep_aifsn * slottime +
		    (IEEE80211_IS_CHAN_5GHZ(c) ?
			IEEE80211_DUR_OFDM_SIFS : IEEE80211_DUR_SIFS);
		rtwn_write_1(sc, wme2reg[ac], aifs);
	}
}