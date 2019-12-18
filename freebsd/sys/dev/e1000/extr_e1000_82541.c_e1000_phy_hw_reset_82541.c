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
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int IGP_ACTIVITY_LED_ENABLE ; 
 int IGP_ACTIVITY_LED_MASK ; 
 int IGP_LED3_MODE ; 
 scalar_t__ e1000_82541 ; 
 scalar_t__ e1000_82547 ; 
 scalar_t__ e1000_phy_hw_reset_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_phy_init_script_82541 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_phy_hw_reset_82541(struct e1000_hw *hw)
{
	s32 ret_val;
	u32 ledctl;

	DEBUGFUNC("e1000_phy_hw_reset_82541");

	ret_val = e1000_phy_hw_reset_generic(hw);
	if (ret_val)
		goto out;

	e1000_phy_init_script_82541(hw);

	if ((hw->mac.type == e1000_82541) || (hw->mac.type == e1000_82547)) {
		/* Configure activity LED after PHY reset */
		ledctl = E1000_READ_REG(hw, E1000_LEDCTL);
		ledctl &= IGP_ACTIVITY_LED_MASK;
		ledctl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
		E1000_WRITE_REG(hw, E1000_LEDCTL, ledctl);
	}

out:
	return ret_val;
}