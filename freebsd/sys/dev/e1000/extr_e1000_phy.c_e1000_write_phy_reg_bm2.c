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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_3__ {int addr; TYPE_2__ ops; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int BM_PHY_PAGE_SELECT ; 
 scalar_t__ BM_WUC_PAGE ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int IGP_PAGE_SHIFT ; 
 int MAX_PHY_MULTI_PAGE_REG ; 
 int MAX_PHY_REG_ADDRESS ; 
 scalar_t__ e1000_access_phy_wakeup_reg_bm (struct e1000_hw*,int,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_write_phy_reg_mdic (struct e1000_hw*,int,scalar_t__) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

s32 e1000_write_phy_reg_bm2(struct e1000_hw *hw, u32 offset, u16 data)
{
	s32 ret_val;
	u16 page = (u16)(offset >> IGP_PAGE_SHIFT);

	DEBUGFUNC("e1000_write_phy_reg_bm2");

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	/* Page 800 works differently than the rest so it has its own func */
	if (page == BM_WUC_PAGE) {
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, &data,
							 FALSE, false);
		goto release;
	}

	hw->phy.addr = 1;

	if (offset > MAX_PHY_MULTI_PAGE_REG) {
		/* Page is shifted left, PHY expects (page x 32) */
		ret_val = e1000_write_phy_reg_mdic(hw, BM_PHY_PAGE_SELECT,
						   page);

		if (ret_val)
			goto release;
	}

	ret_val = e1000_write_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					   data);

release:
	hw->phy.ops.release(hw);
	return ret_val;
}