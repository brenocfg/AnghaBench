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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bwn_phy_n {scalar_t__ hang_avoid; int /*<<< orphan*/  txpwrctrl; } ;
struct bwn_nphy_txgains {int* ipa; int* pad; int* pga; int* txgm; int* tx_lpf; } ;
struct TYPE_2__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_C1_TXPCTL_STAT ; 
 int /*<<< orphan*/  BWN_NPHY_C2_TXPCTL_STAT ; 
 int BWN_NPHY_TXPCTL_STAT_BIDX ; 
 int BWN_NPHY_TXPCTL_STAT_BIDX_SHIFT ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int* bwn_nphy_get_tx_gain_table (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_ntab_read_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static struct bwn_nphy_txgains bwn_nphy_get_tx_gains(struct bwn_mac *mac)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	uint16_t curr_gain[2];
	struct bwn_nphy_txgains target;
	const uint32_t *table = NULL;

	if (!nphy->txpwrctrl) {
		int i;

		if (nphy->hang_avoid)
			bwn_nphy_stay_in_carrier_search(mac, true);
		bwn_ntab_read_bulk(mac, BWN_NTAB16(7, 0x110), 2, curr_gain);
		if (nphy->hang_avoid)
			bwn_nphy_stay_in_carrier_search(mac, false);

		for (i = 0; i < 2; ++i) {
			if (mac->mac_phy.rev >= 7) {
				target.ipa[i] = curr_gain[i] & 0x0007;
				target.pad[i] = (curr_gain[i] & 0x00F8) >> 3;
				target.pga[i] = (curr_gain[i] & 0x0F00) >> 8;
				target.txgm[i] = (curr_gain[i] & 0x7000) >> 12;
				target.tx_lpf[i] = (curr_gain[i] & 0x8000) >> 15;
			} else if (mac->mac_phy.rev >= 3) {
				target.ipa[i] = curr_gain[i] & 0x000F;
				target.pad[i] = (curr_gain[i] & 0x00F0) >> 4;
				target.pga[i] = (curr_gain[i] & 0x0F00) >> 8;
				target.txgm[i] = (curr_gain[i] & 0x7000) >> 12;
			} else {
				target.ipa[i] = curr_gain[i] & 0x0003;
				target.pad[i] = (curr_gain[i] & 0x000C) >> 2;
				target.pga[i] = (curr_gain[i] & 0x0070) >> 4;
				target.txgm[i] = (curr_gain[i] & 0x0380) >> 7;
			}
		}
	} else {
		int i;
		uint16_t index[2];
		index[0] = (BWN_PHY_READ(mac, BWN_NPHY_C1_TXPCTL_STAT) &
			BWN_NPHY_TXPCTL_STAT_BIDX) >>
			BWN_NPHY_TXPCTL_STAT_BIDX_SHIFT;
		index[1] = (BWN_PHY_READ(mac, BWN_NPHY_C2_TXPCTL_STAT) &
			BWN_NPHY_TXPCTL_STAT_BIDX) >>
			BWN_NPHY_TXPCTL_STAT_BIDX_SHIFT;

		for (i = 0; i < 2; ++i) {
			table = bwn_nphy_get_tx_gain_table(mac);
			if (!table)
				break;

			if (mac->mac_phy.rev >= 7) {
				target.ipa[i] = (table[index[i]] >> 16) & 0x7;
				target.pad[i] = (table[index[i]] >> 19) & 0x1F;
				target.pga[i] = (table[index[i]] >> 24) & 0xF;
				target.txgm[i] = (table[index[i]] >> 28) & 0x7;
				target.tx_lpf[i] = (table[index[i]] >> 31) & 0x1;
			} else if (mac->mac_phy.rev >= 3) {
				target.ipa[i] = (table[index[i]] >> 16) & 0xF;
				target.pad[i] = (table[index[i]] >> 20) & 0xF;
				target.pga[i] = (table[index[i]] >> 24) & 0xF;
				target.txgm[i] = (table[index[i]] >> 28) & 0xF;
			} else {
				target.ipa[i] = (table[index[i]] >> 16) & 0x3;
				target.pad[i] = (table[index[i]] >> 18) & 0x3;
				target.pga[i] = (table[index[i]] >> 20) & 0x7;
				target.txgm[i] = (table[index[i]] >> 23) & 0x7;
			}
		}
	}

	return target;
}