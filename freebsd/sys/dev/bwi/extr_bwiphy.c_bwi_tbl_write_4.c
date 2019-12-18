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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bwi_phy {scalar_t__ phy_tbl_data_lo; scalar_t__ phy_tbl_data_hi; scalar_t__ phy_tbl_ctrl; } ;
struct bwi_mac {struct bwi_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,scalar_t__,int) ; 

__attribute__((used)) static void
bwi_tbl_write_4(struct bwi_mac *mac, uint16_t ofs, uint32_t data)
{
	struct bwi_phy *phy = &mac->mac_phy;

	KASSERT(phy->phy_tbl_data_lo != 0 && phy->phy_tbl_data_hi != 0 &&
		 phy->phy_tbl_ctrl != 0,
	    ("phy_tbl_data_lo %d phy_tbl_data_hi %d phy_tbl_ctrl %d",
	      phy->phy_tbl_data_lo, phy->phy_tbl_data_hi, phy->phy_tbl_ctrl));

	PHY_WRITE(mac, phy->phy_tbl_ctrl, ofs);
	PHY_WRITE(mac, phy->phy_tbl_data_hi, data >> 16);
	PHY_WRITE(mac, phy->phy_tbl_data_lo, data & 0xffff);
}