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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_BASE1000T_STATUS ; 
 scalar_t__ E1000_IDLE_ERROR_COUNT_MASK ; 
 int /*<<< orphan*/  E1000_RECEIVE_ERROR_COUNTER ; 
 scalar_t__ E1000_RECEIVE_ERROR_MAX ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

bool e1000_check_phy_82574(struct e1000_hw *hw)
{
	u16 status_1kbt = 0;
	u16 receive_errors = 0;
	s32 ret_val;

	DEBUGFUNC("e1000_check_phy_82574");

	/* Read PHY Receive Error counter first, if its is max - all F's then
	 * read the Base1000T status register If both are max then PHY is hung.
	 */
	ret_val = hw->phy.ops.read_reg(hw, E1000_RECEIVE_ERROR_COUNTER,
				       &receive_errors);
	if (ret_val)
		return FALSE;
	if (receive_errors == E1000_RECEIVE_ERROR_MAX) {
		ret_val = hw->phy.ops.read_reg(hw, E1000_BASE1000T_STATUS,
					       &status_1kbt);
		if (ret_val)
			return FALSE;
		if ((status_1kbt & E1000_IDLE_ERROR_COUNT_MASK) ==
		    E1000_IDLE_ERROR_COUNT_MASK)
			return TRUE;
	}

	return FALSE;
}