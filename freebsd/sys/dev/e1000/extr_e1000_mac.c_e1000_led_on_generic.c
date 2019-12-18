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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ledctl_mode2; } ;
struct TYPE_3__ {int media_type; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_SWDPIN0 ; 
 int /*<<< orphan*/  E1000_CTRL_SWDPIO0 ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  e1000_media_type_copper 129 
#define  e1000_media_type_fiber 128 

s32 e1000_led_on_generic(struct e1000_hw *hw)
{
	u32 ctrl;

	DEBUGFUNC("e1000_led_on_generic");

	switch (hw->phy.media_type) {
	case e1000_media_type_fiber:
		ctrl = E1000_READ_REG(hw, E1000_CTRL);
		ctrl &= ~E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
		E1000_WRITE_REG(hw, E1000_CTRL, ctrl);
		break;
	case e1000_media_type_copper:
		E1000_WRITE_REG(hw, E1000_LEDCTL, hw->mac.ledctl_mode2);
		break;
	default:
		break;
	}

	return E1000_SUCCESS;
}