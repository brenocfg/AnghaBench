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
 int BWN_NPHY_RFCTL_CMD_CHIP0PU ; 
 int BWN_NPHY_RFCTL_CMD_OEPORFORCE ; 
 int BWN_NPHY_RFCTL_CMD_PORFORCE ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bwn_radio_init2055_pre(struct bwn_mac *mac)
{
	BWN_PHY_MASK(mac, BWN_NPHY_RFCTL_CMD,
		     ~BWN_NPHY_RFCTL_CMD_PORFORCE);
	BWN_PHY_SET(mac, BWN_NPHY_RFCTL_CMD,
		    BWN_NPHY_RFCTL_CMD_CHIP0PU |
		    BWN_NPHY_RFCTL_CMD_OEPORFORCE);
	BWN_PHY_SET(mac, BWN_NPHY_RFCTL_CMD,
		    BWN_NPHY_RFCTL_CMD_PORFORCE);
}