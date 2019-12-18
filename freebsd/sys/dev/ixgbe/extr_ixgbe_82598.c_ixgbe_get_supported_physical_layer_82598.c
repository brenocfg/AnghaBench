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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* identify_sfp ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {int type; int sfp_type; TYPE_1__ ops; } ;
struct ixgbe_hw {int device_id; TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int IXGBE_AUTOC_10G_CX4 ; 
 int IXGBE_AUTOC_10G_KX4 ; 
 int IXGBE_AUTOC_10G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_1G_KX ; 
 int IXGBE_AUTOC_1G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_KX4_SUPP ; 
 int IXGBE_AUTOC_KX_SUPP ; 
#define  IXGBE_AUTOC_LMS_10G_LINK_NO_AN 142 
#define  IXGBE_AUTOC_LMS_1G_AN 141 
#define  IXGBE_AUTOC_LMS_1G_LINK_NO_AN 140 
#define  IXGBE_AUTOC_LMS_KX4_AN 139 
#define  IXGBE_AUTOC_LMS_KX4_AN_1G_AN 138 
 int IXGBE_AUTOC_LMS_MASK ; 
#define  IXGBE_DEV_ID_82598AF_DUAL_PORT 137 
#define  IXGBE_DEV_ID_82598AF_SINGLE_PORT 136 
#define  IXGBE_DEV_ID_82598EB_XF_LR 135 
#define  IXGBE_DEV_ID_82598_DA_DUAL_PORT 134 
#define  IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM 133 
 int IXGBE_MDIO_PHY_1000BASET_ABILITY ; 
 int IXGBE_MDIO_PHY_100BASETX_ABILITY ; 
 int IXGBE_MDIO_PHY_10GBASET_ABILITY ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_EXT_ABILITY ; 
 int /*<<< orphan*/  IXGBE_MDIO_PMA_PMD_DEV_TYPE ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_1000BASE_BX ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_1000BASE_KX ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_1000BASE_T ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_100BASE_TX ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_CX4 ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_KX4 ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_LR ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_SR ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_T ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
#define  ixgbe_phy_cu_unknown 132 
 int ixgbe_phy_nl ; 
#define  ixgbe_phy_tn 131 
#define  ixgbe_sfp_type_da_cu 130 
#define  ixgbe_sfp_type_lr 129 
#define  ixgbe_sfp_type_sr 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 

u64 ixgbe_get_supported_physical_layer_82598(struct ixgbe_hw *hw)
{
	u64 physical_layer = IXGBE_PHYSICAL_LAYER_UNKNOWN;
	u32 autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	u32 pma_pmd_10g = autoc & IXGBE_AUTOC_10G_PMA_PMD_MASK;
	u32 pma_pmd_1g = autoc & IXGBE_AUTOC_1G_PMA_PMD_MASK;
	u16 ext_ability = 0;

	DEBUGFUNC("ixgbe_get_supported_physical_layer_82598");

	hw->phy.ops.identify(hw);

	/* Copper PHY must be checked before AUTOC LMS to determine correct
	 * physical layer because 10GBase-T PHYs use LMS = KX4/KX */
	switch (hw->phy.type) {
	case ixgbe_phy_tn:
	case ixgbe_phy_cu_unknown:
		hw->phy.ops.read_reg(hw, IXGBE_MDIO_PHY_EXT_ABILITY,
		IXGBE_MDIO_PMA_PMD_DEV_TYPE, &ext_ability);
		if (ext_ability & IXGBE_MDIO_PHY_10GBASET_ABILITY)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_T;
		if (ext_ability & IXGBE_MDIO_PHY_1000BASET_ABILITY)
			physical_layer |= IXGBE_PHYSICAL_LAYER_1000BASE_T;
		if (ext_ability & IXGBE_MDIO_PHY_100BASETX_ABILITY)
			physical_layer |= IXGBE_PHYSICAL_LAYER_100BASE_TX;
		goto out;
	default:
		break;
	}

	switch (autoc & IXGBE_AUTOC_LMS_MASK) {
	case IXGBE_AUTOC_LMS_1G_AN:
	case IXGBE_AUTOC_LMS_1G_LINK_NO_AN:
		if (pma_pmd_1g == IXGBE_AUTOC_1G_KX)
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_KX;
		else
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_BX;
		break;
	case IXGBE_AUTOC_LMS_10G_LINK_NO_AN:
		if (pma_pmd_10g == IXGBE_AUTOC_10G_CX4)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_CX4;
		else if (pma_pmd_10g == IXGBE_AUTOC_10G_KX4)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_KX4;
		else /* XAUI */
			physical_layer = IXGBE_PHYSICAL_LAYER_UNKNOWN;
		break;
	case IXGBE_AUTOC_LMS_KX4_AN:
	case IXGBE_AUTOC_LMS_KX4_AN_1G_AN:
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_1000BASE_KX;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_KX4;
		break;
	default:
		break;
	}

	if (hw->phy.type == ixgbe_phy_nl) {
		hw->phy.ops.identify_sfp(hw);

		switch (hw->phy.sfp_type) {
		case ixgbe_sfp_type_da_cu:
			physical_layer = IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU;
			break;
		case ixgbe_sfp_type_sr:
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_SR;
			break;
		case ixgbe_sfp_type_lr:
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_LR;
			break;
		default:
			physical_layer = IXGBE_PHYSICAL_LAYER_UNKNOWN;
			break;
		}
	}

	switch (hw->device_id) {
	case IXGBE_DEV_ID_82598_DA_DUAL_PORT:
		physical_layer = IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU;
		break;
	case IXGBE_DEV_ID_82598AF_DUAL_PORT:
	case IXGBE_DEV_ID_82598AF_SINGLE_PORT:
	case IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM:
		physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_SR;
		break;
	case IXGBE_DEV_ID_82598EB_XF_LR:
		physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_LR;
		break;
	default:
		break;
	}

out:
	return physical_layer;
}