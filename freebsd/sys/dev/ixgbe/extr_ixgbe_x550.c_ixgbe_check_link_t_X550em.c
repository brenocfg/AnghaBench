#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_5__ {scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct TYPE_7__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; TYPE_4__ mac; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IXGBE_ERR_CONFIG ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_DEV_TYPE ; 
 int IXGBE_MDIO_AUTO_NEG_LINK_STATUS ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_STATUS ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_check_mac_link_generic (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_check_link_t_X550em(struct ixgbe_hw *hw, ixgbe_link_speed *speed,
			      bool *link_up, bool link_up_wait_to_complete)
{
	u32 status;
	u16 i, autoneg_status = 0;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		return IXGBE_ERR_CONFIG;

	status = ixgbe_check_mac_link_generic(hw, speed, link_up,
					      link_up_wait_to_complete);

	/* If check link fails or MAC link is not up, then return */
	if (status != IXGBE_SUCCESS || !(*link_up))
		return status;

	/* MAC link is up, so check external PHY link.
	 * X557 PHY. Link status is latching low, and can only be used to detect
	 * link drop, and not the current status of the link without performing
	 * back-to-back reads.
	 */
	for (i = 0; i < 2; i++) {
		status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_AUTO_NEG_STATUS,
					      IXGBE_MDIO_AUTO_NEG_DEV_TYPE,
					      &autoneg_status);

		if (status != IXGBE_SUCCESS)
			return status;
	}

	/* If external PHY link is not up, then indicate link not up */
	if (!(autoneg_status & IXGBE_MDIO_AUTO_NEG_LINK_STATUS))
		*link_up = FALSE;

	return IXGBE_SUCCESS;
}