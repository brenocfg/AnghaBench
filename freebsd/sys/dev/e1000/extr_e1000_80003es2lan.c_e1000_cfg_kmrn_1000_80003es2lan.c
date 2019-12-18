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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ DEFAULT_TIPG_IPGT_1000_80003ES2LAN ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_OFFSET_HD_CTRL ; 
 scalar_t__ E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TIPG ; 
 scalar_t__ E1000_TIPG_IPGT_MASK ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GG82563_KMCR_PASS_FALSE_CARRIER ; 
 scalar_t__ GG82563_MAX_KMRN_RETRY ; 
 int /*<<< orphan*/  GG82563_PHY_KMRN_MODE_CTRL ; 
 scalar_t__ e1000_write_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_cfg_kmrn_1000_80003es2lan(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 reg_data, reg_data2;
	u32 tipg;
	u32 i = 0;

	DEBUGFUNC("e1000_configure_kmrn_for_1000");

	reg_data = E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT;
	ret_val =
	    e1000_write_kmrn_reg_80003es2lan(hw,
					     E1000_KMRNCTRLSTA_OFFSET_HD_CTRL,
					     reg_data);
	if (ret_val)
		return ret_val;

	/* Configure Transmit Inter-Packet Gap */
	tipg = E1000_READ_REG(hw, E1000_TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAULT_TIPG_IPGT_1000_80003ES2LAN;
	E1000_WRITE_REG(hw, E1000_TIPG, tipg);

	do {
		ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_KMRN_MODE_CTRL,
					       &reg_data);
		if (ret_val)
			return ret_val;

		ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_KMRN_MODE_CTRL,
					       &reg_data2);
		if (ret_val)
			return ret_val;
		i++;
	} while ((reg_data != reg_data2) && (i < GG82563_MAX_KMRN_RETRY));

	reg_data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;

	return hw->phy.ops.write_reg(hw, GG82563_PHY_KMRN_MODE_CTRL, reg_data);
}