#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* write_reg_page ) (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ rar_entry_count; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_RAR_CTRL (scalar_t__) ; 
 int /*<<< orphan*/  BM_RAR_H (scalar_t__) ; 
 int /*<<< orphan*/  BM_RAR_L (scalar_t__) ; 
 int /*<<< orphan*/  BM_RAR_M (scalar_t__) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_RAH (scalar_t__) ; 
 int E1000_RAH_AV ; 
 int /*<<< orphan*/  E1000_RAL (scalar_t__) ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_disable_phy_wakeup_reg_access_bm (struct e1000_hw*,scalar_t__*) ; 
 scalar_t__ e1000_enable_phy_wakeup_reg_access_bm (struct e1000_hw*,scalar_t__*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*) ; 

void e1000_copy_rx_addrs_to_phy_ich8lan(struct e1000_hw *hw)
{
	u32 mac_reg;
	u16 i, phy_reg = 0;
	s32 ret_val;

	DEBUGFUNC("e1000_copy_rx_addrs_to_phy_ich8lan");

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return;
	ret_val = e1000_enable_phy_wakeup_reg_access_bm(hw, &phy_reg);
	if (ret_val)
		goto release;

	/* Copy both RAL/H (rar_entry_count) and SHRAL/H to PHY */
	for (i = 0; i < (hw->mac.rar_entry_count); i++) {
		mac_reg = E1000_READ_REG(hw, E1000_RAL(i));
		hw->phy.ops.write_reg_page(hw, BM_RAR_L(i),
					   (u16)(mac_reg & 0xFFFF));
		hw->phy.ops.write_reg_page(hw, BM_RAR_M(i),
					   (u16)((mac_reg >> 16) & 0xFFFF));

		mac_reg = E1000_READ_REG(hw, E1000_RAH(i));
		hw->phy.ops.write_reg_page(hw, BM_RAR_H(i),
					   (u16)(mac_reg & 0xFFFF));
		hw->phy.ops.write_reg_page(hw, BM_RAR_CTRL(i),
					   (u16)((mac_reg & E1000_RAH_AV)
						 >> 16));
	}

	e1000_disable_phy_wakeup_reg_access_bm(hw, &phy_reg);

release:
	hw->phy.ops.release(hw);
}