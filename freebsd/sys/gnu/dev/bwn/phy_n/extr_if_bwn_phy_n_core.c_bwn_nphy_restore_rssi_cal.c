#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/ * rssical_phy_regs_5G; int /*<<< orphan*/ * rssical_radio_regs_5G; int /*<<< orphan*/ * rssical_phy_regs_2G; int /*<<< orphan*/ * rssical_radio_regs_2G; } ;
struct TYPE_6__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_5__ {int /*<<< orphan*/  center_freq; } ;
struct bwn_phy_n {TYPE_3__ rssical_cache; TYPE_2__ rssical_chanspec_5G; TYPE_1__ rssical_chanspec_2G; } ;
struct TYPE_8__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_4__ mac_phy; } ;

/* Variables and functions */
 int B2056_RX0 ; 
 int B2056_RX1 ; 
 int B2056_RX_RSSI_MISC ; 
 scalar_t__ BWN_BAND_2G ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0I_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_0Q_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1I_RSSI_Z ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_RSSI_X ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_RSSI_Y ; 
 int /*<<< orphan*/  BWN_NPHY_RSSIMC_1Q_RSSI_Z ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int,int,int /*<<< orphan*/ ) ; 
 int R2057_NB_MASTER_CORE0 ; 
 int R2057_NB_MASTER_CORE1 ; 
 int R2057_VCM_MASK ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_restore_rssi_cal(struct bwn_mac *mac)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	uint16_t *rssical_radio_regs = NULL;
	uint16_t *rssical_phy_regs = NULL;

	if (bwn_current_band(mac) == BWN_BAND_2G) {
		if (!nphy->rssical_chanspec_2G.center_freq)
			return;
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_2G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_2G;
	} else {
		if (!nphy->rssical_chanspec_5G.center_freq)
			return;
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_5G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_5G;
	}

	if (mac->mac_phy.rev >= 19) {
		/* TODO */
	} else if (mac->mac_phy.rev >= 7) {
		BWN_RF_SETMASK(mac, R2057_NB_MASTER_CORE0, ~R2057_VCM_MASK,
				  rssical_radio_regs[0]);
		BWN_RF_SETMASK(mac, R2057_NB_MASTER_CORE1, ~R2057_VCM_MASK,
				  rssical_radio_regs[1]);
	} else {
		BWN_RF_SETMASK(mac, B2056_RX0 | B2056_RX_RSSI_MISC, 0xE3,
				  rssical_radio_regs[0]);
		BWN_RF_SETMASK(mac, B2056_RX1 | B2056_RX_RSSI_MISC, 0xE3,
				  rssical_radio_regs[1]);
	}

	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_RSSI_Z, rssical_phy_regs[0]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_RSSI_Z, rssical_phy_regs[1]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_RSSI_Z, rssical_phy_regs[2]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_RSSI_Z, rssical_phy_regs[3]);

	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_RSSI_X, rssical_phy_regs[4]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_RSSI_X, rssical_phy_regs[5]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_RSSI_X, rssical_phy_regs[6]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_RSSI_X, rssical_phy_regs[7]);

	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0I_RSSI_Y, rssical_phy_regs[8]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_0Q_RSSI_Y, rssical_phy_regs[9]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1I_RSSI_Y, rssical_phy_regs[10]);
	BWN_PHY_WRITE(mac, BWN_NPHY_RSSIMC_1Q_RSSI_Y, rssical_phy_regs[11]);
}