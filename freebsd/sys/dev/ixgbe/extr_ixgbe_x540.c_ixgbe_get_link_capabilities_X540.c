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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_get_copper_link_capabilities_generic (struct ixgbe_hw*,int /*<<< orphan*/ *,int*) ; 

s32 ixgbe_get_link_capabilities_X540(struct ixgbe_hw *hw,
				     ixgbe_link_speed *speed,
				     bool *autoneg)
{
	ixgbe_get_copper_link_capabilities_generic(hw, speed, autoneg);

	return IXGBE_SUCCESS;
}