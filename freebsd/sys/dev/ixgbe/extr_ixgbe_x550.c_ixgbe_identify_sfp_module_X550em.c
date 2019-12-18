#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_identify_module_generic (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_supported_sfp_modules_X550em (struct ixgbe_hw*,int*) ; 

s32 ixgbe_identify_sfp_module_X550em(struct ixgbe_hw *hw)
{
	s32 status;
	bool linear;

	DEBUGFUNC("ixgbe_identify_sfp_module_X550em");

	status = ixgbe_identify_module_generic(hw);

	if (status != IXGBE_SUCCESS)
		return status;

	/* Check if SFP module is supported */
	status = ixgbe_supported_sfp_modules_X550em(hw, &linear);

	return status;
}