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
struct bwn_phy_n {int /*<<< orphan*/ * tx_power_offset; int /*<<< orphan*/ * adj_pwr_tbl; } ;
struct TYPE_2__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_is_40mhz (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_tx_prepare_adjusted_power_table(struct bwn_mac *mac)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	uint8_t idx, delta;
	uint8_t i, stf_mode;

	/* Array adj_pwr_tbl corresponds to the hardware table. It consists of
	 * 21 groups, each containing 4 entries.
	 *
	 * First group has entries for CCK modulation.
	 * The rest of groups has 1 entry per modulation (SISO, CDD, STBC, SDM).
	 *
	 * Group 0 is for CCK
	 * Groups 1..4 use BPSK (group per coding rate)
	 * Groups 5..8 use QPSK (group per coding rate)
	 * Groups 9..12 use 16-QAM (group per coding rate)
	 * Groups 13..16 use 64-QAM (group per coding rate)
	 * Groups 17..20 are unknown
	 */

	for (i = 0; i < 4; i++)
		nphy->adj_pwr_tbl[i] = nphy->tx_power_offset[i];

	for (stf_mode = 0; stf_mode < 4; stf_mode++) {
		delta = 0;
		switch (stf_mode) {
		case 0:
			if (bwn_is_40mhz(mac) && mac->mac_phy.rev >= 5) {
				idx = 68;
			} else {
				delta = 1;
				idx = bwn_is_40mhz(mac) ? 52 : 4;
			}
			break;
		case 1:
			idx = bwn_is_40mhz(mac) ? 76 : 28;
			break;
		case 2:
			idx = bwn_is_40mhz(mac) ? 84 : 36;
			break;
		case 3:
			idx = bwn_is_40mhz(mac) ? 92 : 44;
			break;
		}

		for (i = 0; i < 20; i++) {
			nphy->adj_pwr_tbl[4 + 4 * i + stf_mode] =
				nphy->tx_power_offset[idx];
			if (i == 0)
				idx += delta;
			if (i == 14)
				idx += 1 - delta;
			if (i == 3 || i == 4 || i == 7 || i == 8 || i == 11 ||
			    i == 13)
				idx += 1;
		}
	}
}