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
struct bwn_phy {int rf_ver; int rf_rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  bwn_has_hwpctl (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_hwpctl_early_init(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;

	if (!bwn_has_hwpctl(mac)) {
		BWN_PHY_WRITE(mac, 0x047a, 0xc111);
		return;
	}

	BWN_PHY_MASK(mac, 0x0036, 0xfeff);
	BWN_PHY_WRITE(mac, 0x002f, 0x0202);
	BWN_PHY_SET(mac, 0x047c, 0x0002);
	BWN_PHY_SET(mac, 0x047a, 0xf000);
	if (phy->rf_ver == 0x2050 && phy->rf_rev == 8) {
		BWN_PHY_SETMASK(mac, 0x047a, 0xff0f, 0x0010);
		BWN_PHY_SET(mac, 0x005d, 0x8000);
		BWN_PHY_SETMASK(mac, 0x004e, 0xffc0, 0x0010);
		BWN_PHY_WRITE(mac, 0x002e, 0xc07f);
		BWN_PHY_SET(mac, 0x0036, 0x0400);
	} else {
		BWN_PHY_SET(mac, 0x0036, 0x0200);
		BWN_PHY_SET(mac, 0x0036, 0x0400);
		BWN_PHY_MASK(mac, 0x005d, 0x7fff);
		BWN_PHY_MASK(mac, 0x004f, 0xfffe);
		BWN_PHY_SETMASK(mac, 0x004e, 0xffc0, 0x0010);
		BWN_PHY_WRITE(mac, 0x002e, 0xc07f);
		BWN_PHY_SETMASK(mac, 0x047a, 0xff0f, 0x0010);
	}
}