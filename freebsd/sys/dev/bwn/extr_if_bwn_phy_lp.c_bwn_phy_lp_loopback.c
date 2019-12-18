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
typedef  int uint32_t ;
struct bwn_phy_lp_iq_est {int ie_ipwr; int ie_qpwr; } ;
struct bwn_mac {int dummy; } ;
typedef  int /*<<< orphan*/  ie ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_B2062_N_TXCTL_A ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_ddfs_turnoff (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_ddfs_turnon (struct bwn_mac*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_rx_iq_est (struct bwn_mac*,int,int,struct bwn_phy_lp_iq_est*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rxgain_idx (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_trsw_over (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  memset (struct bwn_phy_lp_iq_est*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bwn_phy_lp_loopback(struct bwn_mac *mac)
{
	struct bwn_phy_lp_iq_est ie;
	int i, index = -1;
	uint32_t tmp;

	memset(&ie, 0, sizeof(ie));

	bwn_phy_lp_set_trsw_over(mac, 1, 1);
	BWN_PHY_SET(mac, BWN_PHY_AFE_CTL_OVR, 1);
	BWN_PHY_MASK(mac, BWN_PHY_AFE_CTL_OVRVAL, 0xfffe);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x800);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0x800);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x8);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0x8);
	BWN_RF_WRITE(mac, BWN_B2062_N_TXCTL_A, 0x80);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_0, 0x80);
	BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_VAL_0, 0x80);
	for (i = 0; i < 32; i++) {
		bwn_phy_lp_set_rxgain_idx(mac, i);
		bwn_phy_lp_ddfs_turnon(mac, 1, 1, 5, 5, 0);
		if (!(bwn_phy_lp_rx_iq_est(mac, 1000, 32, &ie)))
			continue;
		tmp = (ie.ie_ipwr + ie.ie_qpwr) / 1000;
		if ((tmp > 4000) && (tmp < 10000)) {
			index = i;
			break;
		}
	}
	bwn_phy_lp_ddfs_turnoff(mac);
	return (index);
}