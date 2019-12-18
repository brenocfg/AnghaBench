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
struct TYPE_6__ {int /*<<< orphan*/  ledctl_mode1; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFE_PHY_SPECIAL_CONTROL_LED ; 
 int IFE_PSCL_PROBE_LEDS_OFF ; 
 int IFE_PSCL_PROBE_MODE ; 
 scalar_t__ e1000_phy_ife ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_led_off_ich8lan(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_led_off_ich8lan");

	if (hw->phy.type == e1000_phy_ife)
		return hw->phy.ops.write_reg(hw, IFE_PHY_SPECIAL_CONTROL_LED,
			       (IFE_PSCL_PROBE_MODE | IFE_PSCL_PROBE_LEDS_OFF));

	E1000_WRITE_REG(hw, E1000_LEDCTL, hw->mac.ledctl_mode1);
	return E1000_SUCCESS;
}