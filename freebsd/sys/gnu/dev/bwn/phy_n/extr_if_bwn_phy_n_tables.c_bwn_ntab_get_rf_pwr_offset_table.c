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
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct bwn_phy {int rev; int rf_rev; } ;
struct bwn_mac {TYPE_1__* mac_sc; struct bwn_phy mac_phy; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ERRPRINTF (TYPE_1__*,char*) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* bwn_ntab_rf_pwr_offset_2057_rev14_2g ; 
 int /*<<< orphan*/  const* bwn_ntab_rf_pwr_offset_2057_rev9_2g ; 
 int /*<<< orphan*/  const* bwn_ntab_rf_pwr_offset_2057_rev9_5g ; 

const int16_t *bwn_ntab_get_rf_pwr_offset_table(struct bwn_mac *mac)
{
	struct ieee80211com *ic = &mac->mac_sc->sc_ic;
	struct bwn_phy *phy = &mac->mac_phy;

	if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
		switch (phy->rev) {
		case 17:
			if (phy->rf_rev == 14)
				return bwn_ntab_rf_pwr_offset_2057_rev14_2g;
			break;
		case 16:
			if (phy->rf_rev == 9)
				return bwn_ntab_rf_pwr_offset_2057_rev9_2g;
			break;
		}

		BWN_ERRPRINTF(mac->mac_sc,
		       "No 2GHz RF power table available for this device\n");
		return NULL;
	} else {
		switch (phy->rev) {
		case 16:
			if (phy->rf_rev == 9)
				return bwn_ntab_rf_pwr_offset_2057_rev9_5g;
			break;
		}

		BWN_ERRPRINTF(mac->mac_sc,
		       "No 5GHz RF power table available for this device\n");
		return NULL;
	}
}