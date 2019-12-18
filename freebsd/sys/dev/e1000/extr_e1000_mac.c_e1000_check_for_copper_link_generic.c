#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* config_collision_dist ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {TYPE_1__ ops; int /*<<< orphan*/  autoneg; scalar_t__ get_link_status; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_ERR_CONFIG ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  e1000_check_downshift_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_config_fc_after_link_up_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_has_link_generic (struct e1000_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

s32 e1000_check_for_copper_link_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	bool link;

	DEBUGFUNC("e1000_check_for_copper_link");

	/* We only want to go out to the PHY registers to see if Auto-Neg
	 * has completed and/or if our link status has changed.  The
	 * get_link_status flag is set upon receiving a Link Status
	 * Change or Rx Sequence Error interrupt.
	 */
	if (!mac->get_link_status)
		return E1000_SUCCESS;

	/* First we want to see if the MII Status Register reports
	 * link.  If so, then we want to get the current speed/duplex
	 * of the PHY.
	 */
	ret_val = e1000_phy_has_link_generic(hw, 1, 0, &link);
	if (ret_val)
		return ret_val;

	if (!link)
		return E1000_SUCCESS; /* No link detected */

	mac->get_link_status = FALSE;

	/* Check if there was DownShift, must be checked
	 * immediately after link-up
	 */
	e1000_check_downshift_generic(hw);

	/* If we are forcing speed/duplex, then we simply return since
	 * we have already determined whether we have link or not.
	 */
	if (!mac->autoneg)
		return -E1000_ERR_CONFIG;

	/* Auto-Neg is enabled.  Auto Speed Detection takes care
	 * of MAC speed/duplex configuration.  So we only need to
	 * configure Collision Distance in the MAC.
	 */
	mac->ops.config_collision_dist(hw);

	/* Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-autoneg with a
	 * different link partner.
	 */
	ret_val = e1000_config_fc_after_link_up_generic(hw);
	if (ret_val)
		DEBUGOUT("Error configuring flow control\n");

	return ret_val;
}