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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_PHY_RST ; 
 int /*<<< orphan*/  E1000_PHY_CTRL ; 
 int E1000_PHY_CTRL_GBE_DISABLE ; 
 int E1000_PHY_CTRL_NOND0A_GBE_DISABLE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IGP3_VR_CTRL ; 
 int IGP3_VR_CTRL_DEV_POWERDOWN_MODE_MASK ; 
 int IGP3_VR_CTRL_MODE_SHUTDOWN ; 
 int /*<<< orphan*/  e1000_gig_downshift_workaround_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_ich8lan ; 
 scalar_t__ e1000_phy_igp_3 ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 

void e1000_igp3_phy_powerdown_workaround_ich8lan(struct e1000_hw *hw)
{
	u32 reg;
	u16 data;
	u8  retry = 0;

	DEBUGFUNC("e1000_igp3_phy_powerdown_workaround_ich8lan");

	if (hw->phy.type != e1000_phy_igp_3)
		return;

	/* Try the workaround twice (if needed) */
	do {
		/* Disable link */
		reg = E1000_READ_REG(hw, E1000_PHY_CTRL);
		reg |= (E1000_PHY_CTRL_GBE_DISABLE |
			E1000_PHY_CTRL_NOND0A_GBE_DISABLE);
		E1000_WRITE_REG(hw, E1000_PHY_CTRL, reg);

		/* Call gig speed drop workaround on Gig disable before
		 * accessing any PHY registers
		 */
		if (hw->mac.type == e1000_ich8lan)
			e1000_gig_downshift_workaround_ich8lan(hw);

		/* Write VR power-down enable */
		hw->phy.ops.read_reg(hw, IGP3_VR_CTRL, &data);
		data &= ~IGP3_VR_CTRL_DEV_POWERDOWN_MODE_MASK;
		hw->phy.ops.write_reg(hw, IGP3_VR_CTRL,
				      data | IGP3_VR_CTRL_MODE_SHUTDOWN);

		/* Read it back and test */
		hw->phy.ops.read_reg(hw, IGP3_VR_CTRL, &data);
		data &= IGP3_VR_CTRL_DEV_POWERDOWN_MODE_MASK;
		if ((data == IGP3_VR_CTRL_MODE_SHUTDOWN) || retry)
			break;

		/* Issue PHY reset and repeat at most one more time */
		reg = E1000_READ_REG(hw, E1000_CTRL);
		E1000_WRITE_REG(hw, E1000_CTRL, reg | E1000_CTRL_PHY_RST);
		retry++;
	} while (retry);
}