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
struct bwn_phy_n {int bb_mult_save; int lpf_bw_overrode_for_sample_play; scalar_t__ hang_avoid; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_IQLOCAL_CMDGCTL ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_CMD ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_CMD_STOP ; 
 int /*<<< orphan*/  BWN_NPHY_SAMP_STAT ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev19 (struct bwn_mac*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev7 (struct bwn_mac*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bwn_nphy_stop_playback(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	uint16_t tmp;

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 1);

	tmp = BWN_PHY_READ(mac, BWN_NPHY_SAMP_STAT);
	if (tmp & 0x1)
		BWN_PHY_SET(mac, BWN_NPHY_SAMP_CMD, BWN_NPHY_SAMP_CMD_STOP);
	else if (tmp & 0x2)
		BWN_PHY_MASK(mac, BWN_NPHY_IQLOCAL_CMDGCTL, 0x7FFF);

	BWN_PHY_MASK(mac, BWN_NPHY_SAMP_CMD, ~0x0004);

	if (nphy->bb_mult_save & 0x80000000) {
		tmp = nphy->bb_mult_save & 0xFFFF;
		bwn_ntab_write(mac, BWN_NTAB16(15, 87), tmp);
		nphy->bb_mult_save = 0;
	}

	if (phy->rev >= 7 && nphy->lpf_bw_overrode_for_sample_play) {
		if (phy->rev >= 19)
			bwn_nphy_rf_ctl_override_rev19(mac, 0x80, 0, 0, true,
						       1);
		else
			bwn_nphy_rf_ctl_override_rev7(mac, 0x80, 0, 0, true, 1);
		nphy->lpf_bw_overrode_for_sample_play = false;
	}

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 0);
}