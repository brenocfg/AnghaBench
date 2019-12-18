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
 int /*<<< orphan*/  BWN_GPIO_CONTROL ; 
 int /*<<< orphan*/  BWN_GPIO_MASK ; 
 int /*<<< orphan*/  BWN_MACCTL ; 
 int /*<<< orphan*/  BWN_MACCTL_GPOUT_MASK ; 
 int /*<<< orphan*/  BWN_NPHY_GPIO_HIOEN ; 
 int /*<<< orphan*/  BWN_NPHY_GPIO_LOOEN ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_LO1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_LO2 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_WRITE_SETMASK2 (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_SETMASK4 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bwn_gpio_control (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bwn_nphy_superswitch_init(struct bwn_mac *mac, bool init)
{
	int error;

	if (mac->mac_phy.rev >= 7)
		return (0);

	if (mac->mac_phy.rev >= 3) {
		if (!init)
			return (0);
		if (0 /* FIXME */) {
			bwn_ntab_write(mac, BWN_NTAB16(9, 2), 0x211);
			bwn_ntab_write(mac, BWN_NTAB16(9, 3), 0x222);
			bwn_ntab_write(mac, BWN_NTAB16(9, 8), 0x144);
			bwn_ntab_write(mac, BWN_NTAB16(9, 12), 0x188);
		}
	} else {
		BWN_PHY_WRITE(mac, BWN_NPHY_GPIO_LOOEN, 0);
		BWN_PHY_WRITE(mac, BWN_NPHY_GPIO_HIOEN, 0);

		if ((error = bwn_gpio_control(mac, 0xfc00)))
			return (error);

		BWN_WRITE_SETMASK4(mac, BWN_MACCTL, ~BWN_MACCTL_GPOUT_MASK, 0);
		BWN_WRITE_SETMASK2(mac, BWN_GPIO_MASK, ~0, 0xFC00);
		BWN_WRITE_SETMASK2(mac, BWN_GPIO_CONTROL, (~0xFC00 & 0xFFFF),
			      0);

		if (init) {
			BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_LO1, 0x2D8);
			BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_UP1, 0x301);
			BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_LO2, 0x2D8);
			BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_UP2, 0x301);
		}
	}

	return (0);
}