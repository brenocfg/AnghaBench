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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_i2c_eeprom ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* identify_sfp ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {scalar_t__ sfp_type; int type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_1000BASE_SX ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_1000BASE_T ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_LR ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_10GBASE_SR ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_SFP_ACTIVE_DA ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU ; 
 int /*<<< orphan*/  IXGBE_PHYSICAL_LAYER_UNKNOWN ; 
 int IXGBE_SFF_10GBASELR_CAPABLE ; 
 int IXGBE_SFF_10GBASESR_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_10GBE_COMP_CODES ; 
 int IXGBE_SFF_1GBASESX_CAPABLE ; 
 int IXGBE_SFF_1GBASET_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_1GBE_COMP_CODES ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_10GBE_COMP ; 
#define  ixgbe_phy_qsfp_active_unknown 139 
#define  ixgbe_phy_qsfp_intel 138 
#define  ixgbe_phy_qsfp_passive_unknown 137 
#define  ixgbe_phy_qsfp_unknown 136 
#define  ixgbe_phy_sfp_active_unknown 135 
#define  ixgbe_phy_sfp_avago 134 
#define  ixgbe_phy_sfp_ftl 133 
#define  ixgbe_phy_sfp_ftl_active 132 
#define  ixgbe_phy_sfp_intel 131 
#define  ixgbe_phy_sfp_passive_tyco 130 
#define  ixgbe_phy_sfp_passive_unknown 129 
#define  ixgbe_phy_sfp_unknown 128 
 scalar_t__ ixgbe_sfp_type_not_present ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 

u64 ixgbe_get_supported_phy_sfp_layer_generic(struct ixgbe_hw *hw)
{
	u64 physical_layer = IXGBE_PHYSICAL_LAYER_UNKNOWN;
	u8 comp_codes_10g = 0;
	u8 comp_codes_1g = 0;

	DEBUGFUNC("ixgbe_get_supported_phy_sfp_layer_generic");

	hw->phy.ops.identify_sfp(hw);
	if (hw->phy.sfp_type == ixgbe_sfp_type_not_present)
		return physical_layer;

	switch (hw->phy.type) {
	case ixgbe_phy_sfp_passive_tyco:
	case ixgbe_phy_sfp_passive_unknown:
	case ixgbe_phy_qsfp_passive_unknown:
		physical_layer = IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU;
		break;
	case ixgbe_phy_sfp_ftl_active:
	case ixgbe_phy_sfp_active_unknown:
	case ixgbe_phy_qsfp_active_unknown:
		physical_layer = IXGBE_PHYSICAL_LAYER_SFP_ACTIVE_DA;
		break;
	case ixgbe_phy_sfp_avago:
	case ixgbe_phy_sfp_ftl:
	case ixgbe_phy_sfp_intel:
	case ixgbe_phy_sfp_unknown:
		hw->phy.ops.read_i2c_eeprom(hw,
		      IXGBE_SFF_1GBE_COMP_CODES, &comp_codes_1g);
		hw->phy.ops.read_i2c_eeprom(hw,
		      IXGBE_SFF_10GBE_COMP_CODES, &comp_codes_10g);
		if (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_SR;
		else if (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_LR;
		else if (comp_codes_1g & IXGBE_SFF_1GBASET_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_T;
		else if (comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_1000BASE_SX;
		break;
	case ixgbe_phy_qsfp_intel:
	case ixgbe_phy_qsfp_unknown:
		hw->phy.ops.read_i2c_eeprom(hw,
		      IXGBE_SFF_QSFP_10GBE_COMP, &comp_codes_10g);
		if (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_SR;
		else if (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)
			physical_layer = IXGBE_PHYSICAL_LAYER_10GBASE_LR;
		break;
	default:
		break;
	}

	return physical_layer;
}