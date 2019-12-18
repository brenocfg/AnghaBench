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
struct bwn_phy {int analog; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY0 ; 
 int /*<<< orphan*/  BWN_PHY_DACCTL ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_phy_g_set_bbatt(struct bwn_mac *mac,
    uint16_t bbatt)
{
	struct bwn_phy *phy = &mac->mac_phy;

	if (phy->analog == 0) {
		BWN_WRITE_2(mac, BWN_PHY0,
		    (BWN_READ_2(mac, BWN_PHY0) & 0xfff0) | bbatt);
		return;
	}
	if (phy->analog > 1) {
		BWN_PHY_SETMASK(mac, BWN_PHY_DACCTL, 0xffc3, bbatt << 2);
		return;
	}
	BWN_PHY_SETMASK(mac, BWN_PHY_DACCTL, 0xff87, bbatt << 3);
}