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
struct TYPE_4__ {scalar_t__ id; scalar_t__ revision; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT2 (char*,int,int) ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_ID_HIGH ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_ID_LOW ; 
 int /*<<< orphan*/  IXGBE_MDIO_PMA_PMD_DEV_TYPE ; 
 int IXGBE_PHY_REVISION_MASK ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_get_phy_id(struct ixgbe_hw *hw)
{
	u32 status;
	u16 phy_id_high = 0;
	u16 phy_id_low = 0;

	DEBUGFUNC("ixgbe_get_phy_id");

	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_PHY_ID_HIGH,
				      IXGBE_MDIO_PMA_PMD_DEV_TYPE,
				      &phy_id_high);

	if (status == IXGBE_SUCCESS) {
		hw->phy.id = (u32)(phy_id_high << 16);
		status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_PHY_ID_LOW,
					      IXGBE_MDIO_PMA_PMD_DEV_TYPE,
					      &phy_id_low);
		hw->phy.id |= (u32)(phy_id_low & IXGBE_PHY_REVISION_MASK);
		hw->phy.revision = (u32)(phy_id_low & ~IXGBE_PHY_REVISION_MASK);
	}
	DEBUGOUT2("PHY_ID_HIGH 0x%04X, PHY_ID_LOW 0x%04X\n",
		  phy_id_high, phy_id_low);

	return status;
}