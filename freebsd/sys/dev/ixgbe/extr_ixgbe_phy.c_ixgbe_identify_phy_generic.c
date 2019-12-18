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
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ type; int nw_mng_if_sel; scalar_t__ addr; scalar_t__ phy_semaphore_mask; } ;
struct TYPE_3__ {scalar_t__ lan_id; } ;
struct ixgbe_hw {TYPE_2__ phy; TYPE_1__ bus; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_ERR_PHY_ADDR_INVALID ; 
 scalar_t__ IXGBE_GSSR_PHY0_SM ; 
 scalar_t__ IXGBE_GSSR_PHY1_SM ; 
 int IXGBE_MAX_PHY_ADDR ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD ; 
 int IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_phy_unknown ; 
 scalar_t__ ixgbe_probe_phy (struct ixgbe_hw*,int) ; 

s32 ixgbe_identify_phy_generic(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_ERR_PHY_ADDR_INVALID;
	u16 phy_addr;

	DEBUGFUNC("ixgbe_identify_phy_generic");

	if (!hw->phy.phy_semaphore_mask) {
		if (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
		else
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;
	}

	if (hw->phy.type != ixgbe_phy_unknown)
		return IXGBE_SUCCESS;

	if (hw->phy.nw_mng_if_sel) {
		phy_addr = (hw->phy.nw_mng_if_sel &
			    IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD) >>
			   IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT;
		if (ixgbe_probe_phy(hw, phy_addr))
			return IXGBE_SUCCESS;
		else
			return IXGBE_ERR_PHY_ADDR_INVALID;
	}

	for (phy_addr = 0; phy_addr < IXGBE_MAX_PHY_ADDR; phy_addr++) {
		if (ixgbe_probe_phy(hw, phy_addr)) {
			status = IXGBE_SUCCESS;
			break;
		}
	}

	/* Certain media types do not have a phy so an address will not
	 * be found and the code will take this path.  Caller has to
	 * decide if it is an error or not.
	 */
	if (status != IXGBE_SUCCESS)
		hw->phy.addr = 0;

	return status;
}