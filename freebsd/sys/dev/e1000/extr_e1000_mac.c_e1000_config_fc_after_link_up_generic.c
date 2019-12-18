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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {scalar_t__ (* get_link_up_info ) (struct e1000_hw*,scalar_t__*,scalar_t__*) ;} ;
struct e1000_mac_info {scalar_t__ autoneg; TYPE_2__ ops; scalar_t__ autoneg_failed; } ;
struct TYPE_8__ {scalar_t__ requested_mode; void* current_mode; } ;
struct TYPE_5__ {scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_7__ {scalar_t__ media_type; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_4__ fc; TYPE_3__ phy; struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_PCS_ANADV ; 
 int /*<<< orphan*/  E1000_PCS_LCTL ; 
 int E1000_PCS_LCTL_FORCE_FCTRL ; 
 int /*<<< orphan*/  E1000_PCS_LPAB ; 
 int /*<<< orphan*/  E1000_PCS_LSTAT ; 
 int E1000_PCS_LSTS_AN_COMPLETE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int E1000_TXCW_ASM_DIR ; 
 int E1000_TXCW_PAUSE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HALF_DUPLEX ; 
 scalar_t__ MII_SR_AUTONEG_COMPLETE ; 
 scalar_t__ NWAY_AR_ASM_DIR ; 
 scalar_t__ NWAY_AR_PAUSE ; 
 scalar_t__ NWAY_LPAR_ASM_DIR ; 
 scalar_t__ NWAY_LPAR_PAUSE ; 
 int /*<<< orphan*/  PHY_AUTONEG_ADV ; 
 int /*<<< orphan*/  PHY_LP_ABILITY ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 scalar_t__ e1000_fc_full ; 
 void* e1000_fc_none ; 
 void* e1000_fc_rx_pause ; 
 void* e1000_fc_tx_pause ; 
 scalar_t__ e1000_force_mac_fc_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub5 (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 

s32 e1000_config_fc_after_link_up_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;
	u32 pcs_status_reg, pcs_adv_reg, pcs_lp_ability_reg, pcs_ctrl_reg;
	u16 mii_status_reg, mii_nway_adv_reg, mii_nway_lp_ability_reg;
	u16 speed, duplex;

	DEBUGFUNC("e1000_config_fc_after_link_up_generic");

	/* Check for the case where we have fiber media and auto-neg failed
	 * so we had to force link.  In this case, we need to force the
	 * configuration of the MAC to match the "fc" parameter.
	 */
	if (mac->autoneg_failed) {
		if (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_internal_serdes)
			ret_val = e1000_force_mac_fc_generic(hw);
	} else {
		if (hw->phy.media_type == e1000_media_type_copper)
			ret_val = e1000_force_mac_fc_generic(hw);
	}

	if (ret_val) {
		DEBUGOUT("Error forcing flow control settings\n");
		return ret_val;
	}

	/* Check for the case where we have copper media and auto-neg is
	 * enabled.  In this case, we need to check and see if Auto-Neg
	 * has completed, and if so, how the PHY and link partner has
	 * flow control configured.
	 */
	if ((hw->phy.media_type == e1000_media_type_copper) && mac->autoneg) {
		/* Read the MII Status Register and check to see if AutoNeg
		 * has completed.  We read this twice because this reg has
		 * some "sticky" (latched) bits.
		 */
		ret_val = hw->phy.ops.read_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;
		ret_val = hw->phy.ops.read_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;

		if (!(mii_status_reg & MII_SR_AUTONEG_COMPLETE)) {
			DEBUGOUT("Copper PHY and Auto Neg has not completed.\n");
			return ret_val;
		}

		/* The AutoNeg process has completed, so we now need to
		 * read both the Auto Negotiation Advertisement
		 * Register (Address 4) and the Auto_Negotiation Base
		 * Page Ability Register (Address 5) to determine how
		 * flow control was negotiated.
		 */
		ret_val = hw->phy.ops.read_reg(hw, PHY_AUTONEG_ADV,
					       &mii_nway_adv_reg);
		if (ret_val)
			return ret_val;
		ret_val = hw->phy.ops.read_reg(hw, PHY_LP_ABILITY,
					       &mii_nway_lp_ability_reg);
		if (ret_val)
			return ret_val;

		/* Two bits in the Auto Negotiation Advertisement Register
		 * (Address 4) and two bits in the Auto Negotiation Base
		 * Page Ability Register (Address 5) determine flow control
		 * for both the PHY and the link partner.  The following
		 * table, taken out of the IEEE 802.3ab/D6.0 dated March 25,
		 * 1999, describes these PAUSE resolution bits and how flow
		 * control is determined based upon these settings.
		 * NOTE:  DC = Don't Care
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | NIC Resolution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | e1000_fc_none
		 *   0   |    1    |   0   |   DC    | e1000_fc_none
		 *   0   |    1    |   1   |    0    | e1000_fc_none
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 *   1   |    0    |   0   |   DC    | e1000_fc_none
		 *   1   |   DC    |   1   |   DC    | e1000_fc_full
		 *   1   |    1    |   0   |    0    | e1000_fc_none
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_pause
		 *
		 * Are both PAUSE bits set to 1?  If so, this implies
		 * Symmetric Flow Control is enabled at both ends.  The
		 * ASM_DIR bits are irrelevant per the spec.
		 *
		 * For Symmetric Flow Control:
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |   DC    |   1   |   DC    | E1000_fc_full
		 *
		 */
		if ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
		    (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE)) {
			/* Now we need to check if the user selected Rx ONLY
			 * of pause frames.  In this case, we had to advertise
			 * FULL flow control because we could not advertise Rx
			 * ONLY. Hence, we must now check to see if we need to
			 * turn OFF the TRANSMISSION of PAUSE frames.
			 */
			if (hw->fc.requested_mode == e1000_fc_full) {
				hw->fc.current_mode = e1000_fc_full;
				DEBUGOUT("Flow Control = FULL.\n");
			} else {
				hw->fc.current_mode = e1000_fc_rx_pause;
				DEBUGOUT("Flow Control = Rx PAUSE frames only.\n");
			}
		}
		/* For receiving PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 */
		else if (!(mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			  (mii_nway_adv_reg & NWAY_AR_ASM_DIR) &&
			  (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
			  (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_DIR)) {
			hw->fc.current_mode = e1000_fc_tx_pause;
			DEBUGOUT("Flow Control = Tx PAUSE frames only.\n");
		}
		/* For transmitting PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_pause
		 */
		else if ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			 (mii_nway_adv_reg & NWAY_AR_ASM_DIR) &&
			 !(mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
			 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_DIR)) {
			hw->fc.current_mode = e1000_fc_rx_pause;
			DEBUGOUT("Flow Control = Rx PAUSE frames only.\n");
		} else {
			/* Per the IEEE spec, at this point flow control
			 * should be disabled.
			 */
			hw->fc.current_mode = e1000_fc_none;
			DEBUGOUT("Flow Control = NONE.\n");
		}

		/* Now we need to do one last check...  If we auto-
		 * negotiated to HALF DUPLEX, flow control should not be
		 * enabled per IEEE 802.3 spec.
		 */
		ret_val = mac->ops.get_link_up_info(hw, &speed, &duplex);
		if (ret_val) {
			DEBUGOUT("Error getting link speed and duplex\n");
			return ret_val;
		}

		if (duplex == HALF_DUPLEX)
			hw->fc.current_mode = e1000_fc_none;

		/* Now we call a subroutine to actually force the MAC
		 * controller to use the correct flow control settings.
		 */
		ret_val = e1000_force_mac_fc_generic(hw);
		if (ret_val) {
			DEBUGOUT("Error forcing flow control settings\n");
			return ret_val;
		}
	}

	/* Check for the case where we have SerDes media and auto-neg is
	 * enabled.  In this case, we need to check and see if Auto-Neg
	 * has completed, and if so, how the PHY and link partner has
	 * flow control configured.
	 */
	if ((hw->phy.media_type == e1000_media_type_internal_serdes) &&
	    mac->autoneg) {
		/* Read the PCS_LSTS and check to see if AutoNeg
		 * has completed.
		 */
		pcs_status_reg = E1000_READ_REG(hw, E1000_PCS_LSTAT);

		if (!(pcs_status_reg & E1000_PCS_LSTS_AN_COMPLETE)) {
			DEBUGOUT("PCS Auto Neg has not completed.\n");
			return ret_val;
		}

		/* The AutoNeg process has completed, so we now need to
		 * read both the Auto Negotiation Advertisement
		 * Register (PCS_ANADV) and the Auto_Negotiation Base
		 * Page Ability Register (PCS_LPAB) to determine how
		 * flow control was negotiated.
		 */
		pcs_adv_reg = E1000_READ_REG(hw, E1000_PCS_ANADV);
		pcs_lp_ability_reg = E1000_READ_REG(hw, E1000_PCS_LPAB);

		/* Two bits in the Auto Negotiation Advertisement Register
		 * (PCS_ANADV) and two bits in the Auto Negotiation Base
		 * Page Ability Register (PCS_LPAB) determine flow control
		 * for both the PHY and the link partner.  The following
		 * table, taken out of the IEEE 802.3ab/D6.0 dated March 25,
		 * 1999, describes these PAUSE resolution bits and how flow
		 * control is determined based upon these settings.
		 * NOTE:  DC = Don't Care
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | NIC Resolution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | e1000_fc_none
		 *   0   |    1    |   0   |   DC    | e1000_fc_none
		 *   0   |    1    |   1   |    0    | e1000_fc_none
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 *   1   |    0    |   0   |   DC    | e1000_fc_none
		 *   1   |   DC    |   1   |   DC    | e1000_fc_full
		 *   1   |    1    |   0   |    0    | e1000_fc_none
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_pause
		 *
		 * Are both PAUSE bits set to 1?  If so, this implies
		 * Symmetric Flow Control is enabled at both ends.  The
		 * ASM_DIR bits are irrelevant per the spec.
		 *
		 * For Symmetric Flow Control:
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |   DC    |   1   |   DC    | e1000_fc_full
		 *
		 */
		if ((pcs_adv_reg & E1000_TXCW_PAUSE) &&
		    (pcs_lp_ability_reg & E1000_TXCW_PAUSE)) {
			/* Now we need to check if the user selected Rx ONLY
			 * of pause frames.  In this case, we had to advertise
			 * FULL flow control because we could not advertise Rx
			 * ONLY. Hence, we must now check to see if we need to
			 * turn OFF the TRANSMISSION of PAUSE frames.
			 */
			if (hw->fc.requested_mode == e1000_fc_full) {
				hw->fc.current_mode = e1000_fc_full;
				DEBUGOUT("Flow Control = FULL.\n");
			} else {
				hw->fc.current_mode = e1000_fc_rx_pause;
				DEBUGOUT("Flow Control = Rx PAUSE frames only.\n");
			}
		}
		/* For receiving PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_pause
		 */
		else if (!(pcs_adv_reg & E1000_TXCW_PAUSE) &&
			  (pcs_adv_reg & E1000_TXCW_ASM_DIR) &&
			  (pcs_lp_ability_reg & E1000_TXCW_PAUSE) &&
			  (pcs_lp_ability_reg & E1000_TXCW_ASM_DIR)) {
			hw->fc.current_mode = e1000_fc_tx_pause;
			DEBUGOUT("Flow Control = Tx PAUSE frames only.\n");
		}
		/* For transmitting PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_pause
		 */
		else if ((pcs_adv_reg & E1000_TXCW_PAUSE) &&
			 (pcs_adv_reg & E1000_TXCW_ASM_DIR) &&
			 !(pcs_lp_ability_reg & E1000_TXCW_PAUSE) &&
			 (pcs_lp_ability_reg & E1000_TXCW_ASM_DIR)) {
			hw->fc.current_mode = e1000_fc_rx_pause;
			DEBUGOUT("Flow Control = Rx PAUSE frames only.\n");
		} else {
			/* Per the IEEE spec, at this point flow control
			 * should be disabled.
			 */
			hw->fc.current_mode = e1000_fc_none;
			DEBUGOUT("Flow Control = NONE.\n");
		}

		/* Now we call a subroutine to actually force the MAC
		 * controller to use the correct flow control settings.
		 */
		pcs_ctrl_reg = E1000_READ_REG(hw, E1000_PCS_LCTL);
		pcs_ctrl_reg |= E1000_PCS_LCTL_FORCE_FCTRL;
		E1000_WRITE_REG(hw, E1000_PCS_LCTL, pcs_ctrl_reg);

		ret_val = e1000_force_mac_fc_generic(hw);
		if (ret_val) {
			DEBUGOUT("Error forcing flow control settings\n");
			return ret_val;
		}
	}

	return E1000_SUCCESS;
}