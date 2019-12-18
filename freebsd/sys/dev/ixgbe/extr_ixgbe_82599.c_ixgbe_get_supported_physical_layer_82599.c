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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {int type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_AUTOC2 ; 
 int IXGBE_AUTOC2_10G_KR ; 
 int IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK ; 
 int IXGBE_AUTOC2_10G_SFI ; 
 int IXGBE_AUTOC_10G_CX4 ; 
 int IXGBE_AUTOC_10G_KX4 ; 
 int IXGBE_AUTOC_10G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_10G_XAUI ; 
 int IXGBE_AUTOC_1G_KX_BX ; 
 int IXGBE_AUTOC_1G_PMA_PMD_MASK ; 
 int IXGBE_AUTOC_KR_SUPP ; 
 int IXGBE_AUTOC_KX4_SUPP ; 
 int IXGBE_AUTOC_KX_SUPP ; 
#define  IXGBE_AUTOC_LMS_10G_LINK_NO_AN 135 
#define  IXGBE_AUTOC_LMS_10G_SERIAL 134 
#define  IXGBE_AUTOC_LMS_1G_AN 133 
#define  IXGBE_AUTOC_LMS_1G_LINK_NO_AN 132 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR 131 
#define  IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN 130 
 int IXGBE_AUTOC_LMS_MASK ; 
 int IXGBE_MDIO_PHY_1000BASET_ABILITY ; 
 int IXGBE_MDIO_PHY_100BASETX_ABILITY ; 
 int IXGBE_MDIO_PHY_10GBASET_ABILITY ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_EXT_ABILITY ; 
 int /*<<< orphan*/  IXGBE_MDIO_PMA_PMD_DEV_TYPE ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_BX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_KX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_T ; 
 int IXGBE_PHYSICAL_LAYER_100BASE_TX ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_CX4 ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_KR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_KX4 ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_T ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_XAUI ; 
 int IXGBE_PHYSICAL_LAYER_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int ixgbe_get_supported_phy_sfp_layer_generic (struct ixgbe_hw*) ; 
#define  ixgbe_phy_cu_unknown 129 
#define  ixgbe_phy_tn 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

u64 ixgbe_get_supported_physical_layer_82599(struct ixgbe_hw *hw)
{
	u64 physical_layer = IXGBE_PHYSICAL_LAYER_UNKNOWN;
	u32 autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	u32 autoc2 = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	u32 pma_pmd_10g_serial = autoc2 & IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK;
	u32 pma_pmd_10g_parallel = autoc & IXGBE_AUTOC_10G_PMA_PMD_MASK;
	u32 pma_pmd_1g = autoc & IXGBE_AUTOC_1G_PMA_PMD_MASK;
	u16 ext_ability = 0;

	DEBUGFUNC("ixgbe_get_support_physical_layer_82599");

	hw->phy.ops.identify(hw);

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
		if (pma_pmd_1g == IXGBE_AUTOC_1G_KX_BX) {
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_KX |
			    IXGBE_PHYSICAL_LAYER_1000BASE_BX;
			goto out;
		} else
			/* SFI mode so read SFP module */
			goto sfp_check;
		break;
	case IXGBE_AUTOC_LMS_10G_LINK_NO_AN:
		if (pma_pmd_10g_parallel == IXGBE_AUTOC_10G_CX4)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_CX4;
		else if (pma_pmd_10g_parallel == IXGBE_AUTOC_10G_KX4)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_KX4;
		else if (pma_pmd_10g_parallel == IXGBE_AUTOC_10G_XAUI)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_XAUI;
		goto out;
		break;
	case IXGBE_AUTOC_LMS_10G_SERIAL:
		if (pma_pmd_10g_serial == IXGBE_AUTOC2_10G_KR) {
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_KR;
			goto out;
		} else if (pma_pmd_10g_serial == IXGBE_AUTOC2_10G_SFI)
			goto sfp_check;
		break;
	case IXGBE_AUTOC_LMS_KX4_KX_KR:
	case IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN:
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_1000BASE_KX;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_KX4;
		if (autoc & IXGBE_AUTOC_KR_SUPP)
			physical_layer |= IXGBE_PHYSICAL_LAYER_10GBASE_KR;
		goto out;
		break;
	default:
		goto out;
		break;
	}

sfp_check:
	/* SFP check must be done last since DA modules are sometimes used to
	 * test KR mode -  we need to id KR mode correctly before SFP module.
	 * Call identify_sfp because the pluggable module may have changed */
	physical_layer = ixgbe_get_supported_phy_sfp_layer_generic(hw);
out:
	return physical_layer;
}