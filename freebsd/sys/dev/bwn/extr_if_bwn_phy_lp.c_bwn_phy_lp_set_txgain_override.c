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
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  BWN_PHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_phy_lp_set_txgain_override(struct bwn_mac *mac)
{

	if (mac->mac_phy.rev < 2)
		BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_2, 0x100);
	else {
		BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_2, 0x80);
		BWN_PHY_SET(mac, BWN_PHY_RF_OVERRIDE_2, 0x4000);
	}
	BWN_PHY_SET(mac, BWN_PHY_AFE_CTL_OVR, 0x40);
}