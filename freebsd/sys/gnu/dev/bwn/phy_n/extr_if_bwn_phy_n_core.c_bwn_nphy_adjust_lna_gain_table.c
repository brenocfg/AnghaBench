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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct bwn_phy_n {scalar_t__ hang_avoid; scalar_t__ elna_gain_config; scalar_t__ gain_boost; } ;
struct TYPE_2__ {struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ BWN_BAND_2G ; 
 int /*<<< orphan*/  BWN_NPHY_C1_MINGAIN ; 
 int BWN_NPHY_C1_MINGAIN_SHIFT ; 
 int /*<<< orphan*/  BWN_NPHY_C1_MINMAX_GAIN ; 
 int /*<<< orphan*/  BWN_NPHY_C2_MINGAIN ; 
 int BWN_NPHY_C2_MINGAIN_SHIFT ; 
 int /*<<< orphan*/  BWN_NPHY_C2_MINMAX_GAIN ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int bwn_get_chan (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_ntab_write_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void bwn_nphy_adjust_lna_gain_table(struct bwn_mac *mac)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	uint8_t i;
	int16_t tmp;
	uint16_t data[4];
	int16_t gain[2];
	uint16_t minmax[2];
	static const uint16_t lna_gain[4] = { -2, 10, 19, 25 };

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 1);

	if (nphy->gain_boost) {
		if (bwn_current_band(mac) == BWN_BAND_2G) {
			gain[0] = 6;
			gain[1] = 6;
		} else {
			tmp = 40370 - 315 * bwn_get_chan(mac);
			gain[0] = ((tmp >> 13) + ((tmp >> 12) & 1));
			tmp = 23242 - 224 * bwn_get_chan(mac);
			gain[1] = ((tmp >> 13) + ((tmp >> 12) & 1));
		}
	} else {
		gain[0] = 0;
		gain[1] = 0;
	}

	for (i = 0; i < 2; i++) {
		if (nphy->elna_gain_config) {
			data[0] = 19 + gain[i];
			data[1] = 25 + gain[i];
			data[2] = 25 + gain[i];
			data[3] = 25 + gain[i];
		} else {
			data[0] = lna_gain[0] + gain[i];
			data[1] = lna_gain[1] + gain[i];
			data[2] = lna_gain[2] + gain[i];
			data[3] = lna_gain[3] + gain[i];
		}
		bwn_ntab_write_bulk(mac, BWN_NTAB16(i, 8), 4, data);

		minmax[i] = 23 + gain[i];
	}

	BWN_PHY_SETMASK(mac, BWN_NPHY_C1_MINMAX_GAIN, ~BWN_NPHY_C1_MINGAIN,
				minmax[0] << BWN_NPHY_C1_MINGAIN_SHIFT);
	BWN_PHY_SETMASK(mac, BWN_NPHY_C2_MINMAX_GAIN, ~BWN_NPHY_C2_MINGAIN,
				minmax[1] << BWN_NPHY_C2_MINGAIN_SHIFT);

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 0);
}