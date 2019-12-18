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
struct TYPE_4__ {scalar_t__ media_type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_SWDPIN0 ; 
 int /*<<< orphan*/  E1000_CTRL_SWDPIO0 ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_82544 ; 
 scalar_t__ e1000_media_type_copper ; 

__attribute__((used)) static s32 e1000_led_off_82543(struct e1000_hw *hw)
{
	u32 ctrl = E1000_READ_REG(hw, E1000_CTRL);

	DEBUGFUNC("e1000_led_off_82543");

	if (hw->mac.type == e1000_82544 &&
	    hw->phy.media_type == e1000_media_type_copper) {
		/* Set SW-definable Pin 0 to turn off the LED */
		ctrl |= E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
	} else {
		ctrl &= ~E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
	}
	E1000_WRITE_REG(hw, E1000_CTRL, ctrl);

	return E1000_SUCCESS;
}