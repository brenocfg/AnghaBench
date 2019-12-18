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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int (* get_link_up_info ) (struct e1000_hw*,scalar_t__*,scalar_t__*) ;int /*<<< orphan*/  (* config_collision_dist ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {int forced_speed_duplex; scalar_t__ type; TYPE_1__ ops; int /*<<< orphan*/  autoneg; scalar_t__ get_link_status; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int E1000_ALL_10_SPEED ; 
 int E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_ICS ; 
 int E1000_ICS_LSC ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_RCTL_SBP ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 int IMS_ENABLE_MASK ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ TRUE ; 
 scalar_t__ e1000_82544 ; 
 int /*<<< orphan*/  e1000_check_downshift_generic (struct e1000_hw*) ; 
 int e1000_config_fc_after_link_up_generic (struct e1000_hw*) ; 
 int e1000_config_mac_to_phy_82543 (struct e1000_hw*) ; 
 int e1000_phy_has_link_generic (struct e1000_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int e1000_polarity_reversal_workaround_82543 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_set_tbi_sbp_82543 (struct e1000_hw*,scalar_t__) ; 
 scalar_t__ e1000_tbi_compatibility_enabled_82543 (struct e1000_hw*) ; 
 scalar_t__ e1000_tbi_sbp_enabled_82543 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int stub2 (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static s32 e1000_check_for_copper_link_82543(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 icr, rctl;
	s32 ret_val;
	u16 speed, duplex;
	bool link;

	DEBUGFUNC("e1000_check_for_copper_link_82543");

	if (!mac->get_link_status) {
		ret_val = E1000_SUCCESS;
		goto out;
	}

	ret_val = e1000_phy_has_link_generic(hw, 1, 0, &link);
	if (ret_val)
		goto out;

	if (!link)
		goto out; /* No link detected */

	mac->get_link_status = FALSE;

	e1000_check_downshift_generic(hw);

	/*
	 * If we are forcing speed/duplex, then we can return since
	 * we have already determined whether we have link or not.
	 */
	if (!mac->autoneg) {
		/*
		 * If speed and duplex are forced to 10H or 10F, then we will
		 * implement the polarity reversal workaround.  We disable
		 * interrupts first, and upon returning, place the devices
		 * interrupt state to its previous value except for the link
		 * status change interrupt which will happened due to the
		 * execution of this workaround.
		 */
		if (mac->forced_speed_duplex & E1000_ALL_10_SPEED) {
			E1000_WRITE_REG(hw, E1000_IMC, 0xFFFFFFFF);
			ret_val = e1000_polarity_reversal_workaround_82543(hw);
			icr = E1000_READ_REG(hw, E1000_ICR);
			E1000_WRITE_REG(hw, E1000_ICS, (icr & ~E1000_ICS_LSC));
			E1000_WRITE_REG(hw, E1000_IMS, IMS_ENABLE_MASK);
		}

		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	/*
	 * We have a M88E1000 PHY and Auto-Neg is enabled.  If we
	 * have Si on board that is 82544 or newer, Auto
	 * Speed Detection takes care of MAC speed/duplex
	 * configuration.  So we only need to configure Collision
	 * Distance in the MAC.  Otherwise, we need to force
	 * speed/duplex on the MAC to the current PHY speed/duplex
	 * settings.
	 */
	if (mac->type == e1000_82544)
		hw->mac.ops.config_collision_dist(hw);
	else {
		ret_val = e1000_config_mac_to_phy_82543(hw);
		if (ret_val) {
			DEBUGOUT("Error configuring MAC to PHY settings\n");
			goto out;
		}
	}

	/*
	 * Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-autoneg with a
	 * different link partner.
	 */
	ret_val = e1000_config_fc_after_link_up_generic(hw);
	if (ret_val)
		DEBUGOUT("Error configuring flow control\n");

	/*
	 * At this point we know that we are on copper and we have
	 * auto-negotiated link.  These are conditions for checking the link
	 * partner capability register.  We use the link speed to determine if
	 * TBI compatibility needs to be turned on or off.  If the link is not
	 * at gigabit speed, then TBI compatibility is not needed.  If we are
	 * at gigabit speed, we turn on TBI compatibility.
	 */
	if (e1000_tbi_compatibility_enabled_82543(hw)) {
		ret_val = mac->ops.get_link_up_info(hw, &speed, &duplex);
		if (ret_val) {
			DEBUGOUT("Error getting link speed and duplex\n");
			return ret_val;
		}
		if (speed != SPEED_1000) {
			/*
			 * If link speed is not set to gigabit speed,
			 * we do not need to enable TBI compatibility.
			 */
			if (e1000_tbi_sbp_enabled_82543(hw)) {
				/*
				 * If we previously were in the mode,
				 * turn it off.
				 */
				e1000_set_tbi_sbp_82543(hw, FALSE);
				rctl = E1000_READ_REG(hw, E1000_RCTL);
				rctl &= ~E1000_RCTL_SBP;
				E1000_WRITE_REG(hw, E1000_RCTL, rctl);
			}
		} else {
			/*
			 * If TBI compatibility is was previously off,
			 * turn it on. For compatibility with a TBI link
			 * partner, we will store bad packets. Some
			 * frames have an additional byte on the end and
			 * will look like CRC errors to the hardware.
			 */
			if (!e1000_tbi_sbp_enabled_82543(hw)) {
				e1000_set_tbi_sbp_82543(hw, TRUE);
				rctl = E1000_READ_REG(hw, E1000_RCTL);
				rctl |= E1000_RCTL_SBP;
				E1000_WRITE_REG(hw, E1000_RCTL, rctl);
			}
		}
	}
out:
	return ret_val;
}