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
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CCMCTL ; 
 int /*<<< orphan*/  E1000_GIOCTL ; 
 int /*<<< orphan*/  E1000_SCCTL ; 
 int /*<<< orphan*/  E1000_SCTL ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ e1000_82575 ; 
 int /*<<< orphan*/  e1000_write_8bit_ctrl_reg_generic (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static s32 e1000_reset_init_script_82575(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_reset_init_script_82575");

	if (hw->mac.type == e1000_82575) {
		DEBUGOUT("Running reset init script for 82575\n");
		/* SerDes configuration via SERDESCTRL */
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCTL, 0x00, 0x0C);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCTL, 0x01, 0x78);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCTL, 0x1B, 0x23);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCTL, 0x23, 0x15);

		/* CCM configuration via CCMCTL register */
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_CCMCTL, 0x14, 0x00);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_CCMCTL, 0x10, 0x00);

		/* PCIe lanes configuration */
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_GIOCTL, 0x00, 0xEC);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_GIOCTL, 0x61, 0xDF);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_GIOCTL, 0x34, 0x05);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_GIOCTL, 0x2F, 0x81);

		/* PCIe PLL Configuration */
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCCTL, 0x02, 0x47);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCCTL, 0x14, 0x00);
		e1000_write_8bit_ctrl_reg_generic(hw, E1000_SCCTL, 0x10, 0x00);
	}

	return E1000_SUCCESS;
}