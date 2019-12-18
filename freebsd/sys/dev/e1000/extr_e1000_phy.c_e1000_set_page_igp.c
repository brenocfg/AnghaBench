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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int addr; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PAGE_SELECT ; 
 int /*<<< orphan*/  e1000_write_phy_reg_mdic (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 e1000_set_page_igp(struct e1000_hw *hw, u16 page)
{
	DEBUGFUNC("e1000_set_page_igp");

	DEBUGOUT1("Setting page 0x%x\n", page);

	hw->phy.addr = 1;

	return e1000_write_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT, page);
}