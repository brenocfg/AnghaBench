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
struct TYPE_3__ {int /*<<< orphan*/  reset; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_PHY ; 
 int /*<<< orphan*/  IXGBE_NOT_IMPLEMENTED ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_call_func (struct ixgbe_hw*,int /*<<< orphan*/ ,struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_identify_phy (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_phy_unknown ; 

s32 ixgbe_reset_phy(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_SUCCESS;

	if (hw->phy.type == ixgbe_phy_unknown) {
		if (ixgbe_identify_phy(hw) != IXGBE_SUCCESS)
			status = IXGBE_ERR_PHY;
	}

	if (status == IXGBE_SUCCESS) {
		status = ixgbe_call_func(hw, hw->phy.ops.reset, (hw),
					 IXGBE_NOT_IMPLEMENTED);
	}
	return status;
}