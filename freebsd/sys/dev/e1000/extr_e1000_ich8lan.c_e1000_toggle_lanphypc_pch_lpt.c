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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_LPCD ; 
 int E1000_CTRL_LANPHYPC_OVERRIDE ; 
 int E1000_CTRL_LANPHYPC_VALUE ; 
 int /*<<< orphan*/  E1000_FEXTNVM3 ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_pch_lpt ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static void e1000_toggle_lanphypc_pch_lpt(struct e1000_hw *hw)
{
	u32 mac_reg;

	DEBUGFUNC("e1000_toggle_lanphypc_pch_lpt");

	/* Set Phy Config Counter to 50msec */
	mac_reg = E1000_READ_REG(hw, E1000_FEXTNVM3);
	mac_reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
	mac_reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
	E1000_WRITE_REG(hw, E1000_FEXTNVM3, mac_reg);

	/* Toggle LANPHYPC Value bit */
	mac_reg = E1000_READ_REG(hw, E1000_CTRL);
	mac_reg |= E1000_CTRL_LANPHYPC_OVERRIDE;
	mac_reg &= ~E1000_CTRL_LANPHYPC_VALUE;
	E1000_WRITE_REG(hw, E1000_CTRL, mac_reg);
	E1000_WRITE_FLUSH(hw);
	msec_delay(1);
	mac_reg &= ~E1000_CTRL_LANPHYPC_OVERRIDE;
	E1000_WRITE_REG(hw, E1000_CTRL, mac_reg);
	E1000_WRITE_FLUSH(hw);

	if (hw->mac.type < e1000_pch_lpt) {
		msec_delay(50);
	} else {
		u16 count = 20;

		do {
			msec_delay(5);
		} while (!(E1000_READ_REG(hw, E1000_CTRL_EXT) &
			   E1000_CTRL_EXT_LPCD) && count--);

		msec_delay(30);
	}
}