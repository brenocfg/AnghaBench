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
 int /*<<< orphan*/  BWN_NPHY_RFCTL_CMD ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_CMD_CHIP0PU ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_CMD_OEPORFORCE ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_radio_2057_init_pre(struct bwn_mac *mac)
{
	BWN_PHY_MASK(mac, BWN_NPHY_RFCTL_CMD, ~BWN_NPHY_RFCTL_CMD_CHIP0PU);
	/* Maybe wl meant to reset and set (order?) RFCTL_CMD_OEPORFORCE? */
	BWN_PHY_MASK(mac, BWN_NPHY_RFCTL_CMD, BWN_NPHY_RFCTL_CMD_OEPORFORCE);
	BWN_PHY_SET(mac, BWN_NPHY_RFCTL_CMD, ~BWN_NPHY_RFCTL_CMD_OEPORFORCE);
	BWN_PHY_SET(mac, BWN_NPHY_RFCTL_CMD, BWN_NPHY_RFCTL_CMD_CHIP0PU);
}