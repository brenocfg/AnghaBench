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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_ID_HIGH ; 
 int /*<<< orphan*/  IXGBE_MDIO_PMA_PMD_DEV_TYPE ; 
 int TRUE ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

bool ixgbe_validate_phy_addr(struct ixgbe_hw *hw, u32 phy_addr)
{
	u16 phy_id = 0;
	bool valid = FALSE;

	DEBUGFUNC("ixgbe_validate_phy_addr");

	hw->phy.addr = phy_addr;
	hw->phy.ops.read_reg(hw, IXGBE_MDIO_PHY_ID_HIGH,
			     IXGBE_MDIO_PMA_PMD_DEV_TYPE, &phy_id);

	if (phy_id != 0xFFFF && phy_id != 0x0)
		valid = TRUE;

	DEBUGOUT1("PHY ID HIGH is 0x%04X\n", phy_id);

	return valid;
}