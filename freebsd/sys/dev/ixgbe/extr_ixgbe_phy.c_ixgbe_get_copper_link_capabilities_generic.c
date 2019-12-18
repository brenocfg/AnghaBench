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
struct TYPE_2__ {scalar_t__ speeds_supported; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  scalar_t__ ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int TRUE ; 
 int /*<<< orphan*/  ixgbe_get_copper_speeds_supported (struct ixgbe_hw*) ; 

s32 ixgbe_get_copper_link_capabilities_generic(struct ixgbe_hw *hw,
					       ixgbe_link_speed *speed,
					       bool *autoneg)
{
	s32 status = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_get_copper_link_capabilities_generic");

	*autoneg = TRUE;
	if (!hw->phy.speeds_supported)
		status = ixgbe_get_copper_speeds_supported(hw);

	*speed = hw->phy.speeds_supported;
	return status;
}