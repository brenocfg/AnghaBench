#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_10__ {int requested_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* read ) (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ;} ;
struct TYPE_9__ {TYPE_3__ ops; } ;
struct TYPE_7__ {scalar_t__ type; int autoneg; } ;
struct TYPE_6__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_5__ fc; TYPE_4__ nvm; TYPE_2__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
#define  E1000_CTRL_EXT_LINK_MODE_1000BASE_KX 132 
 int E1000_CTRL_EXT_LINK_MODE_MASK ; 
#define  E1000_CTRL_EXT_LINK_MODE_SGMII 131 
 int E1000_CTRL_EXT_SDP3_DATA ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_SLU ; 
 int E1000_CTRL_SPD_1000 ; 
 int E1000_CTRL_SWDPIN0 ; 
 int E1000_CTRL_SWDPIN1 ; 
 int E1000_EEPROM_PCS_AUTONEG_DISABLE_BIT ; 
 int /*<<< orphan*/  E1000_PCS_ANADV ; 
 int /*<<< orphan*/  E1000_PCS_LCTL ; 
 int E1000_PCS_LCTL_AN_ENABLE ; 
 int E1000_PCS_LCTL_AN_RESTART ; 
 int E1000_PCS_LCTL_AN_TIMEOUT ; 
 int E1000_PCS_LCTL_FDV_FULL ; 
 int E1000_PCS_LCTL_FLV_LINK_UP ; 
 int E1000_PCS_LCTL_FORCE_FCTRL ; 
 int E1000_PCS_LCTL_FORCE_LINK ; 
 int E1000_PCS_LCTL_FSD ; 
 int E1000_PCS_LCTL_FSV_1000 ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SCTL ; 
 int E1000_SCTL_DISABLE_SERDES_LOOPBACK ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int E1000_TXCW_ASM_DIR ; 
 int E1000_TXCW_PAUSE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  NVM_COMPAT ; 
 int TRUE ; 
 scalar_t__ e1000_82575 ; 
 scalar_t__ e1000_82576 ; 
#define  e1000_fc_full 130 
#define  e1000_fc_rx_pause 129 
#define  e1000_fc_tx_pause 128 
 int /*<<< orphan*/  e1000_force_mac_fc_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_sgmii_active_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static s32 e1000_setup_serdes_link_82575(struct e1000_hw *hw)
{
	u32 ctrl_ext, ctrl_reg, reg, anadv_reg;
	bool pcs_autoneg;
	s32 ret_val = E1000_SUCCESS;
	u16 data;

	DEBUGFUNC("e1000_setup_serdes_link_82575");

	if ((hw->phy.media_type != e1000_media_type_internal_serdes) &&
	    !e1000_sgmii_active_82575(hw))
		return ret_val;

	/*
	 * On the 82575, SerDes loopback mode persists until it is
	 * explicitly turned off or a power cycle is performed.  A read to
	 * the register does not indicate its status.  Therefore, we ensure
	 * loopback mode is disabled during initialization.
	 */
	E1000_WRITE_REG(hw, E1000_SCTL, E1000_SCTL_DISABLE_SERDES_LOOPBACK);

	/* power on the sfp cage if present */
	ctrl_ext = E1000_READ_REG(hw, E1000_CTRL_EXT);
	ctrl_ext &= ~E1000_CTRL_EXT_SDP3_DATA;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);

	ctrl_reg = E1000_READ_REG(hw, E1000_CTRL);
	ctrl_reg |= E1000_CTRL_SLU;

	/* set both sw defined pins on 82575/82576*/
	if (hw->mac.type == e1000_82575 || hw->mac.type == e1000_82576)
		ctrl_reg |= E1000_CTRL_SWDPIN0 | E1000_CTRL_SWDPIN1;

	reg = E1000_READ_REG(hw, E1000_PCS_LCTL);

	/* default pcs_autoneg to the same setting as mac autoneg */
	pcs_autoneg = hw->mac.autoneg;

	switch (ctrl_ext & E1000_CTRL_EXT_LINK_MODE_MASK) {
	case E1000_CTRL_EXT_LINK_MODE_SGMII:
		/* sgmii mode lets the phy handle forcing speed/duplex */
		pcs_autoneg = TRUE;
		/* autoneg time out should be disabled for SGMII mode */
		reg &= ~(E1000_PCS_LCTL_AN_TIMEOUT);
		break;
	case E1000_CTRL_EXT_LINK_MODE_1000BASE_KX:
		/* disable PCS autoneg and support parallel detect only */
		pcs_autoneg = FALSE;
		/* FALLTHROUGH */
	default:
		if (hw->mac.type == e1000_82575 ||
		    hw->mac.type == e1000_82576) {
			ret_val = hw->nvm.ops.read(hw, NVM_COMPAT, 1, &data);
			if (ret_val) {
				DEBUGOUT("NVM Read Error\n");
				return ret_val;
			}

			if (data & E1000_EEPROM_PCS_AUTONEG_DISABLE_BIT)
				pcs_autoneg = FALSE;
		}

		/*
		 * non-SGMII modes only supports a speed of 1000/Full for the
		 * link so it is best to just force the MAC and let the pcs
		 * link either autoneg or be forced to 1000/Full
		 */
		ctrl_reg |= E1000_CTRL_SPD_1000 | E1000_CTRL_FRCSPD |
			    E1000_CTRL_FD | E1000_CTRL_FRCDPX;

		/* set speed of 1000/Full if speed/duplex is forced */
		reg |= E1000_PCS_LCTL_FSV_1000 | E1000_PCS_LCTL_FDV_FULL;
		break;
	}

	E1000_WRITE_REG(hw, E1000_CTRL, ctrl_reg);

	/*
	 * New SerDes mode allows for forcing speed or autonegotiating speed
	 * at 1gb. Autoneg should be default set by most drivers. This is the
	 * mode that will be compatible with older link partners and switches.
	 * However, both are supported by the hardware and some drivers/tools.
	 */
	reg &= ~(E1000_PCS_LCTL_AN_ENABLE | E1000_PCS_LCTL_FLV_LINK_UP |
		 E1000_PCS_LCTL_FSD | E1000_PCS_LCTL_FORCE_LINK);

	if (pcs_autoneg) {
		/* Set PCS register for autoneg */
		reg |= E1000_PCS_LCTL_AN_ENABLE | /* Enable Autoneg */
		       E1000_PCS_LCTL_AN_RESTART; /* Restart autoneg */

		/* Disable force flow control for autoneg */
		reg &= ~E1000_PCS_LCTL_FORCE_FCTRL;

		/* Configure flow control advertisement for autoneg */
		anadv_reg = E1000_READ_REG(hw, E1000_PCS_ANADV);
		anadv_reg &= ~(E1000_TXCW_ASM_DIR | E1000_TXCW_PAUSE);

		switch (hw->fc.requested_mode) {
		case e1000_fc_full:
		case e1000_fc_rx_pause:
			anadv_reg |= E1000_TXCW_ASM_DIR;
			anadv_reg |= E1000_TXCW_PAUSE;
			break;
		case e1000_fc_tx_pause:
			anadv_reg |= E1000_TXCW_ASM_DIR;
			break;
		default:
			break;
		}

		E1000_WRITE_REG(hw, E1000_PCS_ANADV, anadv_reg);

		DEBUGOUT1("Configuring Autoneg:PCS_LCTL=0x%08X\n", reg);
	} else {
		/* Set PCS register for forced link */
		reg |= E1000_PCS_LCTL_FSD;	/* Force Speed */

		/* Force flow control for forced link */
		reg |= E1000_PCS_LCTL_FORCE_FCTRL;

		DEBUGOUT1("Configuring Forced Link:PCS_LCTL=0x%08X\n", reg);
	}

	E1000_WRITE_REG(hw, E1000_PCS_LCTL, reg);

	if (!pcs_autoneg && !e1000_sgmii_active_82575(hw))
		e1000_force_mac_fc_generic(hw);

	return ret_val;
}