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
struct TYPE_2__ {scalar_t__ phy_do_full_init; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  R2057_RFPLL_MASTER ; 
 int /*<<< orphan*/  R2057_RFPLL_MISC_CAL_RESETN ; 
 int /*<<< orphan*/  R2057_XTALPUOVR_PINCTRL ; 
 int /*<<< orphan*/  R2057_XTAL_CONFIG2 ; 
 int /*<<< orphan*/  bwn_radio_2057_rcal (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_radio_2057_rccal (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_radio_2057_init_post(struct bwn_mac *mac)
{
	BWN_RF_SET(mac, R2057_XTALPUOVR_PINCTRL, 0x1);

	if (0) /* FIXME: Is this BCM43217 specific? */
		BWN_RF_SET(mac, R2057_XTALPUOVR_PINCTRL, 0x2);

	BWN_RF_SET(mac, R2057_RFPLL_MISC_CAL_RESETN, 0x78);
	BWN_RF_SET(mac, R2057_XTAL_CONFIG2, 0x80);
	DELAY(2000);
	BWN_RF_MASK(mac, R2057_RFPLL_MISC_CAL_RESETN, ~0x78);
	BWN_RF_MASK(mac, R2057_XTAL_CONFIG2, ~0x80);

	if (mac->mac_phy.phy_do_full_init) {
		bwn_radio_2057_rcal(mac);
		bwn_radio_2057_rccal(mac);
	}
	BWN_RF_MASK(mac, R2057_RFPLL_MASTER, ~0x8);
}