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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_DEV_TYPE ; 
 int IXGBE_MDIO_AUTO_NEG_LINK_STATUS ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_STATUS ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static s32 ixgbe_ext_phy_t_x550em_get_link(struct ixgbe_hw *hw, bool *link_up)
{
	u32 ret;
	u16 autoneg_status;

	*link_up = FALSE;

	/* read this twice back to back to indicate current status */
	ret = hw->phy.ops.read_reg(hw, IXGBE_MDIO_AUTO_NEG_STATUS,
				   IXGBE_MDIO_AUTO_NEG_DEV_TYPE,
				   &autoneg_status);
	if (ret != IXGBE_SUCCESS)
		return ret;

	ret = hw->phy.ops.read_reg(hw, IXGBE_MDIO_AUTO_NEG_STATUS,
				   IXGBE_MDIO_AUTO_NEG_DEV_TYPE,
				   &autoneg_status);
	if (ret != IXGBE_SUCCESS)
		return ret;

	*link_up = !!(autoneg_status & IXGBE_MDIO_AUTO_NEG_LINK_STATUS);

	return IXGBE_SUCCESS;
}