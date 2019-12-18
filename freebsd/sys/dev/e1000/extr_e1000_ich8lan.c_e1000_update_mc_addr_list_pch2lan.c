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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* write_reg_page ) (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int mta_reg_count; int* mta_shadow; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BM_MTA (int) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  e1000_disable_phy_wakeup_reg_access_bm (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_enable_phy_wakeup_reg_access_bm (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*) ; 

__attribute__((used)) static void e1000_update_mc_addr_list_pch2lan(struct e1000_hw *hw,
					      u8 *mc_addr_list,
					      u32 mc_addr_count)
{
	u16 phy_reg = 0;
	int i;
	s32 ret_val;

	DEBUGFUNC("e1000_update_mc_addr_list_pch2lan");

	e1000_update_mc_addr_list_generic(hw, mc_addr_list, mc_addr_count);

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return;

	ret_val = e1000_enable_phy_wakeup_reg_access_bm(hw, &phy_reg);
	if (ret_val)
		goto release;

	for (i = 0; i < hw->mac.mta_reg_count; i++) {
		hw->phy.ops.write_reg_page(hw, BM_MTA(i),
					   (u16)(hw->mac.mta_shadow[i] &
						 0xFFFF));
		hw->phy.ops.write_reg_page(hw, (BM_MTA(i) + 1),
					   (u16)((hw->mac.mta_shadow[i] >> 16) &
						 0xFFFF));
	}

	e1000_disable_phy_wakeup_reg_access_bm(hw, &phy_reg);

release:
	hw->phy.ops.release(hw);
}