#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {void* media_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  e100_base_fx; } ;
struct e1000_dev_spec_82575 {TYPE_2__ eth_flags; void* sgmii_active; void* module_plugged; } ;
struct TYPE_4__ {struct e1000_dev_spec_82575 _82575; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ dev_spec; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
#define  E1000_CTRL_EXT_LINK_MODE_1000BASE_KX 131 
#define  E1000_CTRL_EXT_LINK_MODE_GMII 130 
 int E1000_CTRL_EXT_LINK_MODE_MASK ; 
#define  E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES 129 
#define  E1000_CTRL_EXT_LINK_MODE_SGMII 128 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 void* FALSE ; 
 void* TRUE ; 
 void* e1000_media_type_copper ; 
 void* e1000_media_type_internal_serdes ; 
 void* e1000_media_type_unknown ; 
 int /*<<< orphan*/  e1000_set_sfp_media_type_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_sgmii_uses_mdio_82575 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_get_media_type_82575(struct e1000_hw *hw)
{
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	s32 ret_val = E1000_SUCCESS;
	u32 ctrl_ext = 0;
	u32 link_mode = 0;

	/* Set internal phy as default */
	dev_spec->sgmii_active = FALSE;
	dev_spec->module_plugged = FALSE;

	/* Get CSR setting */
	ctrl_ext = E1000_READ_REG(hw, E1000_CTRL_EXT);

	/* extract link mode setting */
	link_mode = ctrl_ext & E1000_CTRL_EXT_LINK_MODE_MASK;

	switch (link_mode) {
	case E1000_CTRL_EXT_LINK_MODE_1000BASE_KX:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		break;
	case E1000_CTRL_EXT_LINK_MODE_GMII:
		hw->phy.media_type = e1000_media_type_copper;
		break;
	case E1000_CTRL_EXT_LINK_MODE_SGMII:
		/* Get phy control interface type set (MDIO vs. I2C)*/
		if (e1000_sgmii_uses_mdio_82575(hw)) {
			hw->phy.media_type = e1000_media_type_copper;
			dev_spec->sgmii_active = TRUE;
			break;
		}
		/* fall through for I2C based SGMII */
		/* FALLTHROUGH */
	case E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES:
		/* read media type from SFP EEPROM */
		ret_val = e1000_set_sfp_media_type_82575(hw);
		if ((ret_val != E1000_SUCCESS) ||
		    (hw->phy.media_type == e1000_media_type_unknown)) {
			/*
			 * If media type was not identified then return media
			 * type defined by the CTRL_EXT settings.
			 */
			hw->phy.media_type = e1000_media_type_internal_serdes;

			if (link_mode == E1000_CTRL_EXT_LINK_MODE_SGMII) {
				hw->phy.media_type = e1000_media_type_copper;
				dev_spec->sgmii_active = TRUE;
			}

			break;
		}

		/* do not change link mode for 100BaseFX */
		if (dev_spec->eth_flags.e100_base_fx)
			break;

		/* change current link mode setting */
		ctrl_ext &= ~E1000_CTRL_EXT_LINK_MODE_MASK;

		if (hw->phy.media_type == e1000_media_type_copper)
			ctrl_ext |= E1000_CTRL_EXT_LINK_MODE_SGMII;
		else
			ctrl_ext |= E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;

		E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);

		break;
	}

	return ret_val;
}