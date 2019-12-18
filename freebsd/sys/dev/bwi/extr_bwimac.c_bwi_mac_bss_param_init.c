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
typedef  int uint16_t ;
struct ieee80211com {int /*<<< orphan*/ * ic_sup_rates; } ;
struct ieee80211_rate_table {int dummy; } ;
struct bwi_softc {struct ieee80211com sc_ic; } ;
struct bwi_retry_lim {int /*<<< orphan*/  lgretry_fb; int /*<<< orphan*/  lgretry; int /*<<< orphan*/  shretry_fb; int /*<<< orphan*/  shretry; } ;
struct bwi_phy {size_t phy_mode; } ;
struct bwi_mac {struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;
typedef  int /*<<< orphan*/  lim ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_80211_MOBJ ; 
 int /*<<< orphan*/  BWI_80211_MOBJ_CWMAX ; 
 int /*<<< orphan*/  BWI_80211_MOBJ_CWMIN ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_PROBE_RESP_TO ; 
 int /*<<< orphan*/  BWI_LGRETRY ; 
 int /*<<< orphan*/  BWI_LGRETRY_FB ; 
 int /*<<< orphan*/  BWI_SHRETRY ; 
 int /*<<< orphan*/  BWI_SHRETRY_FB ; 
 int /*<<< orphan*/  IEEE80211_CHAN_B ; 
 int /*<<< orphan*/  IEEE80211_CHAN_G ; 
 int IEEE80211_CW_MAX ; 
 int IEEE80211_CW_MIN_0 ; 
 int IEEE80211_CW_MIN_1 ; 
 size_t IEEE80211_MODE_11B ; 
 size_t IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwi_mac_set_ackrates (struct bwi_mac*,struct ieee80211_rate_table const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwi_mac_set_retry_lim (struct bwi_mac*,struct bwi_retry_lim*) ; 
 int /*<<< orphan*/  bzero (struct bwi_retry_lim*,int) ; 
 int /*<<< orphan*/  ieee80211_find_channel (struct ieee80211com*,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_rate_table* ieee80211_get_ratetable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_mac_bss_param_init(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	struct ieee80211com *ic = &sc->sc_ic;
	const struct ieee80211_rate_table *rt;
	struct bwi_retry_lim lim;
	uint16_t cw_min;

	/*
	 * Set short/long retry limits
	 */
	bzero(&lim, sizeof(lim));
	lim.shretry = BWI_SHRETRY;
	lim.shretry_fb = BWI_SHRETRY_FB;
	lim.lgretry = BWI_LGRETRY;
	lim.lgretry_fb = BWI_LGRETRY_FB;
	bwi_mac_set_retry_lim(mac, &lim);

	/*
	 * Implicitly prevent firmware from sending probe response
	 * by setting its "probe response timeout" to 1us.
	 */
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_PROBE_RESP_TO, 1);

	/*
	 * XXX MAC level acknowledge and CW min/max should depend
	 * on the char rateset of the IBSS/BSS to join.
	 * XXX this is all wrong; should be done on channel change
	 */
	if (phy->phy_mode == IEEE80211_MODE_11B) {
		rt = ieee80211_get_ratetable(
		    ieee80211_find_channel(ic, 2412, IEEE80211_CHAN_B));
		bwi_mac_set_ackrates(mac, rt,
		    &ic->ic_sup_rates[IEEE80211_MODE_11B]);
	} else {
		rt = ieee80211_get_ratetable(
		    ieee80211_find_channel(ic, 2412, IEEE80211_CHAN_G));
		bwi_mac_set_ackrates(mac, rt,
		    &ic->ic_sup_rates[IEEE80211_MODE_11G]);
	}

	/*
	 * Set CW min
	 */
	if (phy->phy_mode == IEEE80211_MODE_11B)
		cw_min = IEEE80211_CW_MIN_0;
	else
		cw_min = IEEE80211_CW_MIN_1;
	MOBJ_WRITE_2(mac, BWI_80211_MOBJ, BWI_80211_MOBJ_CWMIN, cw_min);

	/*
	 * Set CW max
	 */
	MOBJ_WRITE_2(mac, BWI_80211_MOBJ, BWI_80211_MOBJ_CWMAX,
		     IEEE80211_CW_MAX);
}