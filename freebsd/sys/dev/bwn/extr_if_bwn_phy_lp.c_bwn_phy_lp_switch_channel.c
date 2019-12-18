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
typedef  int /*<<< orphan*/  uint32_t ;
struct bwn_phy_lp {int /*<<< orphan*/  plp_chan; } ;
struct bwn_phy {int rf_ver; struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_CHANNEL ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bwn_phy_lp_b2062_switch_channel (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int bwn_phy_lp_b2063_switch_channel (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_anafilter (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_gaintbl (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ieee2mhz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bwn_phy_lp_switch_channel(struct bwn_mac *mac, uint32_t chan)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_lp *plp = &phy->phy_lp;
	int error;

	if (phy->rf_ver == 0x2063) {
		error = bwn_phy_lp_b2063_switch_channel(mac, chan);
		if (error)
			return (error);
	} else {
		error = bwn_phy_lp_b2062_switch_channel(mac, chan);
		if (error)
			return (error);
		bwn_phy_lp_set_anafilter(mac, chan);
		bwn_phy_lp_set_gaintbl(mac, ieee80211_ieee2mhz(chan, 0));
	}

	plp->plp_chan = chan;
	BWN_WRITE_2(mac, BWN_CHANNEL, chan);
	return (0);
}