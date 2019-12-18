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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  BWN_PHY_AFE_CTL_OVRVAL ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

void
bwn_phy_lp_switch_analog(struct bwn_mac *mac, int on)
{

	if (on) {
		BWN_PHY_MASK(mac, BWN_PHY_AFE_CTL_OVR, 0xfff8);
		return;
	}

	BWN_PHY_SET(mac, BWN_PHY_AFE_CTL_OVRVAL, 0x0007);
	BWN_PHY_SET(mac, BWN_PHY_AFE_CTL_OVR, 0x0007);
}