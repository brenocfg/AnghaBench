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
struct TYPE_4__ {scalar_t__ (* reset_hw ) (struct ixgbe_hw*) ;scalar_t__ (* start_hw ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* init_led_link_act ) (struct ixgbe_hw*) ;} ;
struct TYPE_3__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,scalar_t__) ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_PRESENT ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 

s32 ixgbe_init_hw_generic(struct ixgbe_hw *hw)
{
	s32 status;

	DEBUGFUNC("ixgbe_init_hw_generic");

	/* Reset the hardware */
	status = hw->mac.ops.reset_hw(hw);

	if (status == IXGBE_SUCCESS || status == IXGBE_ERR_SFP_NOT_PRESENT) {
		/* Start the HW */
		status = hw->mac.ops.start_hw(hw);
	}

	/* Initialize the LED link active for LED blink support */
	if (hw->mac.ops.init_led_link_act)
		hw->mac.ops.init_led_link_act(hw);

	if (status != IXGBE_SUCCESS)
		DEBUGOUT1("Failed to initialize HW, STATUS = %d\n", status);

	return status;
}