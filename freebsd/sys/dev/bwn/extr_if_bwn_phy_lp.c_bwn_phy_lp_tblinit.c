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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_phy_lp_get_default_chan (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_gaintbl (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_lp_tblinit_r01 (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_tblinit_r2 (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_lp_tblinit_txgain (struct bwn_mac*) ; 
 int /*<<< orphan*/  ieee80211_ieee2mhz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_phy_lp_tblinit(struct bwn_mac *mac)
{
	uint32_t freq = ieee80211_ieee2mhz(bwn_phy_lp_get_default_chan(mac), 0);

	if (mac->mac_phy.rev < 2) {
		bwn_phy_lp_tblinit_r01(mac);
		bwn_phy_lp_tblinit_txgain(mac);
		bwn_phy_lp_set_gaintbl(mac, freq);
		return;
	}

	bwn_phy_lp_tblinit_r2(mac);
	bwn_phy_lp_tblinit_txgain(mac);
}