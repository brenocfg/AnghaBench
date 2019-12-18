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
struct TYPE_2__ {int /*<<< orphan*/  autotry_restart; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ixgbe_start_hw_gen2 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_start_hw_generic (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_verify_fw_version_82599 (struct ixgbe_hw*) ; 

s32 ixgbe_start_hw_82599(struct ixgbe_hw *hw)
{
	s32 ret_val = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_start_hw_82599");

	ret_val = ixgbe_start_hw_generic(hw);
	if (ret_val != IXGBE_SUCCESS)
		goto out;

	ret_val = ixgbe_start_hw_gen2(hw);
	if (ret_val != IXGBE_SUCCESS)
		goto out;

	/* We need to run link autotry after the driver loads */
	hw->mac.autotry_restart = TRUE;

	if (ret_val == IXGBE_SUCCESS)
		ret_val = ixgbe_verify_fw_version_82599(hw);
out:
	return ret_val;
}