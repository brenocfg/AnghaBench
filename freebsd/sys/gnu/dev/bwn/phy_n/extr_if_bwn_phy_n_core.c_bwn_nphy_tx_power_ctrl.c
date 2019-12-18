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
typedef  int uint16_t ;
struct bwn_phy_n {int txpwrctrl; int* tx_pwr_idx; scalar_t__ hang_avoid; int /*<<< orphan*/  adj_pwr_tbl; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;
typedef  scalar_t__ bwn_band_t ;

/* Variables and functions */
 scalar_t__ BWN_BAND_5G ; 
 int BWN_HF_TSSI_RESET_PSM_WORKAROUN ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  BWN_NPHY_BPHY_CTL3 ; 
 int BWN_NPHY_BPHY_CTL3_SCALE ; 
 int /*<<< orphan*/  BWN_NPHY_C1_TXPCTL_STAT ; 
 int /*<<< orphan*/  BWN_NPHY_C2_TXPCTL_STAT ; 
 int /*<<< orphan*/  BWN_NPHY_PAPD_EN0 ; 
 int /*<<< orphan*/  BWN_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  BWN_NPHY_TABLE_ADDR ; 
 int /*<<< orphan*/  BWN_NPHY_TABLE_DATALO ; 
 int /*<<< orphan*/  BWN_NPHY_TXPCTL_CMD ; 
 int BWN_NPHY_TXPCTL_CMD_COEFF ; 
 int BWN_NPHY_TXPCTL_CMD_HWPCTLEN ; 
 int BWN_NPHY_TXPCTL_CMD_INIT ; 
 int BWN_NPHY_TXPCTL_CMD_PCTLEN ; 
 int /*<<< orphan*/  BWN_NPHY_TXPCTL_INIT ; 
 int BWN_NPHY_TXPCTL_INIT_PIDXI1 ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 
 scalar_t__ bwn_is_40mhz (struct bwn_mac*) ; 
 scalar_t__ bwn_nphy_ipa (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_ntab_write_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_nphy_tx_power_ctrl(struct bwn_mac *mac, bool enable)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	uint8_t i;
	uint16_t bmask, val, tmp;
	bwn_band_t band = bwn_current_band(mac);

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 1);

	nphy->txpwrctrl = enable;
	if (!enable) {
		if (mac->mac_phy.rev >= 3 &&
		    (BWN_PHY_READ(mac, BWN_NPHY_TXPCTL_CMD) &
		     (BWN_NPHY_TXPCTL_CMD_COEFF |
		      BWN_NPHY_TXPCTL_CMD_HWPCTLEN |
		      BWN_NPHY_TXPCTL_CMD_PCTLEN))) {
			/* We disable enabled TX pwr ctl, save it's state */
			nphy->tx_pwr_idx[0] = BWN_PHY_READ(mac,
						BWN_NPHY_C1_TXPCTL_STAT) & 0x7f;
			nphy->tx_pwr_idx[1] = BWN_PHY_READ(mac,
						BWN_NPHY_C2_TXPCTL_STAT) & 0x7f;
		}

		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR, 0x6840);
		for (i = 0; i < 84; i++)
			BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0);

		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR, 0x6C40);
		for (i = 0; i < 84; i++)
			BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0);

		tmp = BWN_NPHY_TXPCTL_CMD_COEFF | BWN_NPHY_TXPCTL_CMD_HWPCTLEN;
		if (mac->mac_phy.rev >= 3)
			tmp |= BWN_NPHY_TXPCTL_CMD_PCTLEN;
		BWN_PHY_MASK(mac, BWN_NPHY_TXPCTL_CMD, ~tmp);

		if (mac->mac_phy.rev >= 3) {
			BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER1, 0x0100);
			BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER, 0x0100);
		} else {
			BWN_PHY_SET(mac, BWN_NPHY_AFECTL_OVER, 0x4000);
		}

		if (mac->mac_phy.rev == 2)
			BWN_PHY_SETMASK(mac, BWN_NPHY_BPHY_CTL3,
				~BWN_NPHY_BPHY_CTL3_SCALE, 0x53);
		else if (mac->mac_phy.rev < 2)
			BWN_PHY_SETMASK(mac, BWN_NPHY_BPHY_CTL3,
				~BWN_NPHY_BPHY_CTL3_SCALE, 0x5A);

		if (mac->mac_phy.rev < 2 && bwn_is_40mhz(mac))
			bwn_hf_write(mac, bwn_hf_read(mac) | BWN_HF_TSSI_RESET_PSM_WORKAROUN);
	} else {
		bwn_ntab_write_bulk(mac, BWN_NTAB16(26, 64), 84,
				    nphy->adj_pwr_tbl);
		bwn_ntab_write_bulk(mac, BWN_NTAB16(27, 64), 84,
				    nphy->adj_pwr_tbl);

		bmask = BWN_NPHY_TXPCTL_CMD_COEFF |
			BWN_NPHY_TXPCTL_CMD_HWPCTLEN;
		/* wl does useless check for "enable" param here */
		val = BWN_NPHY_TXPCTL_CMD_COEFF | BWN_NPHY_TXPCTL_CMD_HWPCTLEN;
		if (mac->mac_phy.rev >= 3) {
			bmask |= BWN_NPHY_TXPCTL_CMD_PCTLEN;
			if (val)
				val |= BWN_NPHY_TXPCTL_CMD_PCTLEN;
		}
		BWN_PHY_SETMASK(mac, BWN_NPHY_TXPCTL_CMD, ~(bmask), val);

		if (band == BWN_BAND_5G) {
			if (phy->rev >= 19) {
				/* TODO */
			} else if (phy->rev >= 7) {
				BWN_PHY_SETMASK(mac, BWN_NPHY_TXPCTL_CMD,
						~BWN_NPHY_TXPCTL_CMD_INIT,
						0x32);
				BWN_PHY_SETMASK(mac, BWN_NPHY_TXPCTL_INIT,
						~BWN_NPHY_TXPCTL_INIT_PIDXI1,
						0x32);
			} else {
				BWN_PHY_SETMASK(mac, BWN_NPHY_TXPCTL_CMD,
						~BWN_NPHY_TXPCTL_CMD_INIT,
						0x64);
				if (phy->rev > 1)
					BWN_PHY_SETMASK(mac,
							BWN_NPHY_TXPCTL_INIT,
							~BWN_NPHY_TXPCTL_INIT_PIDXI1,
							0x64);
			}
		}

		if (mac->mac_phy.rev >= 3) {
			if (nphy->tx_pwr_idx[0] != 128 &&
			    nphy->tx_pwr_idx[1] != 128) {
				/* Recover TX pwr ctl state */
				BWN_PHY_SETMASK(mac, BWN_NPHY_TXPCTL_CMD,
						~BWN_NPHY_TXPCTL_CMD_INIT,
						nphy->tx_pwr_idx[0]);
				if (mac->mac_phy.rev > 1)
					BWN_PHY_SETMASK(mac,
						BWN_NPHY_TXPCTL_INIT,
						~0xff, nphy->tx_pwr_idx[1]);
			}
		}

		if (phy->rev >= 7) {
			/* TODO */
		}

		if (mac->mac_phy.rev >= 3) {
			BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_OVER1, ~0x100);
			BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_OVER, ~0x100);
		} else {
			BWN_PHY_MASK(mac, BWN_NPHY_AFECTL_OVER, ~0x4000);
		}

		if (mac->mac_phy.rev == 2)
			BWN_PHY_SETMASK(mac, BWN_NPHY_BPHY_CTL3, ~0xFF, 0x3b);
		else if (mac->mac_phy.rev < 2)
			BWN_PHY_SETMASK(mac, BWN_NPHY_BPHY_CTL3, ~0xFF, 0x40);

		if (mac->mac_phy.rev < 2 && bwn_is_40mhz(mac))
			bwn_hf_write(mac, bwn_hf_read(mac) & ~BWN_HF_TSSI_RESET_PSM_WORKAROUN);

		if (bwn_nphy_ipa(mac)) {
			BWN_PHY_MASK(mac, BWN_NPHY_PAPD_EN0, ~0x4);
			BWN_PHY_MASK(mac, BWN_NPHY_PAPD_EN1, ~0x4);
		}
	}

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 0);
}