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
struct bwi_phy {int phy_rev; } ;
struct bwi_mac {struct bwi_phy mac_phy; } ;
struct bwi_gains {int tbl_gain1; int tbl_gain2; int phy_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int /*<<< orphan*/  bwi_mac_dummy_xmit (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_tbl_write_2 (struct bwi_mac*,int,int) ; 

void
bwi_set_gains(struct bwi_mac *mac, const struct bwi_gains *gains)
{
	struct bwi_phy *phy = &mac->mac_phy;
	uint16_t tbl_gain_ofs1, tbl_gain_ofs2, tbl_gain;
	int i;

	if (phy->phy_rev <= 1) {
		tbl_gain_ofs1 = 0x5000;
		tbl_gain_ofs2 = tbl_gain_ofs1 + 16;
	} else {
		tbl_gain_ofs1 = 0x400;
		tbl_gain_ofs2 = tbl_gain_ofs1 + 8;
	}

	for (i = 0; i < 4; ++i) {
		if (gains != NULL) {
			tbl_gain = gains->tbl_gain1;
		} else {
			/* Bit swap */
			tbl_gain = (i & 0x1) << 1;
			tbl_gain |= (i & 0x2) >> 1;
		}
		bwi_tbl_write_2(mac, tbl_gain_ofs1 + i, tbl_gain);
	}

	for (i = 0; i < 16; ++i) {
		if (gains != NULL)
			tbl_gain = gains->tbl_gain2;
		else
			tbl_gain = i;
		bwi_tbl_write_2(mac, tbl_gain_ofs2 + i, tbl_gain);
	}

	if (gains == NULL || (gains != NULL && gains->phy_gain != -1)) {
		uint16_t phy_gain1, phy_gain2;

		if (gains != NULL) {
			phy_gain1 =
			((uint16_t)gains->phy_gain << 14) |
			((uint16_t)gains->phy_gain << 6);
			phy_gain2 = phy_gain1;
		} else {
			phy_gain1 = 0x4040;
			phy_gain2 = 0x4000;
		}
		PHY_FILT_SETBITS(mac, 0x4a0, 0xbfbf, phy_gain1);
		PHY_FILT_SETBITS(mac, 0x4a1, 0xbfbf, phy_gain1);
		PHY_FILT_SETBITS(mac, 0x4a2, 0xbfbf, phy_gain2);
	}
	bwi_mac_dummy_xmit(mac);
}