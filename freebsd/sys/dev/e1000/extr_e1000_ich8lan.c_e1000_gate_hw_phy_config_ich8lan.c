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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EXTCNF_CTRL ; 
 int /*<<< orphan*/  E1000_EXTCNF_CTRL_GATE_PHY_CFG ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_pch2lan ; 

__attribute__((used)) static void e1000_gate_hw_phy_config_ich8lan(struct e1000_hw *hw, bool gate)
{
	u32 extcnf_ctrl;

	DEBUGFUNC("e1000_gate_hw_phy_config_ich8lan");

	if (hw->mac.type < e1000_pch2lan)
		return;

	extcnf_ctrl = E1000_READ_REG(hw, E1000_EXTCNF_CTRL);

	if (gate)
		extcnf_ctrl |= E1000_EXTCNF_CTRL_GATE_PHY_CFG;
	else
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_GATE_PHY_CFG;

	E1000_WRITE_REG(hw, E1000_EXTCNF_CTRL, extcnf_ctrl);
}