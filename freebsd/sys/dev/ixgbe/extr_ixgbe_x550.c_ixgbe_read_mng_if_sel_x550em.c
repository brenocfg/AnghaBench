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
struct TYPE_4__ {int nw_mng_if_sel; int addr; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_NW_MNG_IF_SEL ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_ACT ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_mac_X550EM_a ; 

__attribute__((used)) static s32 ixgbe_read_mng_if_sel_x550em(struct ixgbe_hw *hw)
{
	/* Save NW management interface connected on board. This is used
	 * to determine internal PHY mode.
	 */
	hw->phy.nw_mng_if_sel = IXGBE_READ_REG(hw, IXGBE_NW_MNG_IF_SEL);

	/* If X552 (X550EM_a) and MDIO is connected to external PHY, then set
	 * PHY address. This register field was has only been used for X552.
	 */
	if (hw->mac.type == ixgbe_mac_X550EM_a &&
	    hw->phy.nw_mng_if_sel & IXGBE_NW_MNG_IF_SEL_MDIO_ACT) {
		hw->phy.addr = (hw->phy.nw_mng_if_sel &
				IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD) >>
			       IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT;
	}

	return IXGBE_SUCCESS;
}