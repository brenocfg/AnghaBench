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
struct TYPE_7__ {scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_8__ {int nw_mng_if_sel; TYPE_3__ ops; } ;
struct TYPE_5__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_CONFIG ; 
 scalar_t__ IXGBE_ERR_INVALID_LINK_SETTINGS ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_DEV_TYPE ; 
 int /*<<< orphan*/  IXGBE_MDIO_AUTO_NEG_VENDOR_STAT ; 
#define  IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_10GB_FULL 129 
#define  IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_1GB_FULL 128 
 int IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_MASK ; 
 int IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_ext_phy_t_x550em_get_link (struct ixgbe_hw*,int*) ; 
 scalar_t__ ixgbe_mac_X550EM_x ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ ixgbe_setup_ixfi_x550em (struct ixgbe_hw*,int*) ; 
 scalar_t__ ixgbe_setup_kr_speed_x550em (struct ixgbe_hw*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_setup_internal_phy_t_x550em(struct ixgbe_hw *hw)
{
	ixgbe_link_speed force_speed;
	bool link_up;
	u32 status;
	u16 speed;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		return IXGBE_ERR_CONFIG;

	if (hw->mac.type == ixgbe_mac_X550EM_x &&
	    !(hw->phy.nw_mng_if_sel & IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE)) {
		/* If link is down, there is no setup necessary so return  */
		status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
		if (status != IXGBE_SUCCESS)
			return status;

		if (!link_up)
			return IXGBE_SUCCESS;

		status = hw->phy.ops.read_reg(hw,
					      IXGBE_MDIO_AUTO_NEG_VENDOR_STAT,
					      IXGBE_MDIO_AUTO_NEG_DEV_TYPE,
					      &speed);
		if (status != IXGBE_SUCCESS)
			return status;

		/* If link is still down - no setup is required so return */
		status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
		if (status != IXGBE_SUCCESS)
			return status;
		if (!link_up)
			return IXGBE_SUCCESS;

		/* clear everything but the speed and duplex bits */
		speed &= IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_MASK;

		switch (speed) {
		case IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_10GB_FULL:
			force_speed = IXGBE_LINK_SPEED_10GB_FULL;
			break;
		case IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_1GB_FULL:
			force_speed = IXGBE_LINK_SPEED_1GB_FULL;
			break;
		default:
			/* Internal PHY does not support anything else */
			return IXGBE_ERR_INVALID_LINK_SETTINGS;
		}

		return ixgbe_setup_ixfi_x550em(hw, &force_speed);
	} else {
		speed = IXGBE_LINK_SPEED_10GB_FULL |
			IXGBE_LINK_SPEED_1GB_FULL;
		return ixgbe_setup_kr_speed_x550em(hw, speed);
	}
}