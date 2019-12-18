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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_MDIO_PHY_SET_LOW_POWER_MODE ; 
 int /*<<< orphan*/  IXGBE_MDIO_VENDOR_SPECIFIC_1_CONTROL ; 
 int /*<<< orphan*/  IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_mng_present (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 ixgbe_set_copper_phy_power(struct ixgbe_hw *hw, bool on)
{
	u32 status;
	u16 reg;

	if (!on && ixgbe_mng_present(hw))
		return 0;

	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_VENDOR_SPECIFIC_1_CONTROL,
				      IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				      &reg);
	if (status)
		return status;

	if (on) {
		reg &= ~IXGBE_MDIO_PHY_SET_LOW_POWER_MODE;
	} else {
		if (ixgbe_check_reset_blocked(hw))
			return 0;
		reg |= IXGBE_MDIO_PHY_SET_LOW_POWER_MODE;
	}

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_VENDOR_SPECIFIC_1_CONTROL,
				       IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				       reg);
	return status;
}