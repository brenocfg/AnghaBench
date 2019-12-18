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

/* Variables and functions */
 int /*<<< orphan*/  PHY_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  bwi_tbl_write_2 (struct bwi_mac*,int,int) ; 

__attribute__((used)) static void
bwi_phy_config_agc(struct bwi_mac *mac)
{
	struct bwi_phy *phy = &mac->mac_phy;
	uint16_t ofs;

	ofs = phy->phy_rev == 1 ? 0x4c00 : 0;

	bwi_tbl_write_2(mac, ofs, 0xfe);
	bwi_tbl_write_2(mac, ofs + 1, 0xd);
	bwi_tbl_write_2(mac, ofs + 2, 0x13);
	bwi_tbl_write_2(mac, ofs + 3, 0x19);

	if (phy->phy_rev == 1) {
		bwi_tbl_write_2(mac, 0x1800, 0x2710);
		bwi_tbl_write_2(mac, 0x1801, 0x9b83);
		bwi_tbl_write_2(mac, 0x1802, 0x9b83);
		bwi_tbl_write_2(mac, 0x1803, 0xf8d);
		PHY_WRITE(mac, 0x455, 0x4);
	}

	PHY_FILT_SETBITS(mac, 0x4a5, 0xff, 0x5700);
	PHY_FILT_SETBITS(mac, 0x41a, 0xff80, 0xf);
	PHY_FILT_SETBITS(mac, 0x41a, 0xc07f, 0x2b80);
	PHY_FILT_SETBITS(mac, 0x48c, 0xf0ff, 0x300);

	RF_SETBITS(mac, 0x7a, 0x8);

	PHY_FILT_SETBITS(mac, 0x4a0, 0xfff0, 0x8);
	PHY_FILT_SETBITS(mac, 0x4a1, 0xf0ff, 0x600);
	PHY_FILT_SETBITS(mac, 0x4a2, 0xf0ff, 0x700);
	PHY_FILT_SETBITS(mac, 0x4a0, 0xf0ff, 0x100);

	if (phy->phy_rev == 1)
		PHY_FILT_SETBITS(mac, 0x4a2, 0xfff0, 0x7);

	PHY_FILT_SETBITS(mac, 0x488, 0xff00, 0x1c);
	PHY_FILT_SETBITS(mac, 0x488, 0xc0ff, 0x200);
	PHY_FILT_SETBITS(mac, 0x496, 0xff00, 0x1c);
	PHY_FILT_SETBITS(mac, 0x489, 0xff00, 0x20);
	PHY_FILT_SETBITS(mac, 0x489, 0xc0ff, 0x200);
	PHY_FILT_SETBITS(mac, 0x482, 0xff00, 0x2e);
	PHY_FILT_SETBITS(mac, 0x496, 0xff, 0x1a00);
	PHY_FILT_SETBITS(mac, 0x481, 0xff00, 0x28);
	PHY_FILT_SETBITS(mac, 0x481, 0xff, 0x2c00);

	if (phy->phy_rev == 1) {
		PHY_WRITE(mac, 0x430, 0x92b);
		PHY_FILT_SETBITS(mac, 0x41b, 0xffe1, 0x2);
	} else {
		PHY_CLRBITS(mac, 0x41b, 0x1e);
		PHY_WRITE(mac, 0x41f, 0x287a);
		PHY_FILT_SETBITS(mac, 0x420, 0xfff0, 0x4);

		if (phy->phy_rev >= 6) {
			PHY_WRITE(mac, 0x422, 0x287a);
			PHY_FILT_SETBITS(mac, 0x420, 0xfff, 0x3000);
		}
	}

	PHY_FILT_SETBITS(mac, 0x4a8, 0x8080, 0x7874);
	PHY_WRITE(mac, 0x48e, 0x1c00);

	if (phy->phy_rev == 1) {
		PHY_FILT_SETBITS(mac, 0x4ab, 0xf0ff, 0x600);
		PHY_WRITE(mac, 0x48b, 0x5e);
		PHY_FILT_SETBITS(mac, 0x48c, 0xff00, 0x1e);
		PHY_WRITE(mac, 0x48d, 0x2);
	}

	bwi_tbl_write_2(mac, ofs + 0x800, 0);
	bwi_tbl_write_2(mac, ofs + 0x801, 7);
	bwi_tbl_write_2(mac, ofs + 0x802, 16);
	bwi_tbl_write_2(mac, ofs + 0x803, 28);

	if (phy->phy_rev >= 6) {
		PHY_CLRBITS(mac, 0x426, 0x3);
		PHY_CLRBITS(mac, 0x426, 0x1000);
	}
}