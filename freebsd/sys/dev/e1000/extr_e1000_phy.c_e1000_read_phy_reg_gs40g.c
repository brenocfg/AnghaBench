#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int GS40G_OFFSET_MASK ; 
 int /*<<< orphan*/  GS40G_PAGE_SELECT ; 
 int GS40G_PAGE_SHIFT ; 
 scalar_t__ e1000_read_phy_reg_mdic (struct e1000_hw*,int,int*) ; 
 scalar_t__ e1000_write_phy_reg_mdic (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

s32 e1000_read_phy_reg_gs40g(struct e1000_hw *hw, u32 offset, u16 *data)
{
	s32 ret_val;
	u16 page = offset >> GS40G_PAGE_SHIFT;

	DEBUGFUNC("e1000_read_phy_reg_gs40g");

	offset = offset & GS40G_OFFSET_MASK;
	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	ret_val = e1000_write_phy_reg_mdic(hw, GS40G_PAGE_SELECT, page);
	if (ret_val)
		goto release;
	ret_val = e1000_read_phy_reg_mdic(hw, offset, data);

release:
	hw->phy.ops.release(hw);
	return ret_val;
}