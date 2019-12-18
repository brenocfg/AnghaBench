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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {scalar_t__ vendor_id; int device_id; TYPE_1__ mac; int /*<<< orphan*/  mvals; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_REPORT2 (int /*<<< orphan*/ ,char*,int) ; 
#define  IXGBE_DEV_ID_82598 177 
#define  IXGBE_DEV_ID_82598AF_DUAL_PORT 176 
#define  IXGBE_DEV_ID_82598AF_SINGLE_PORT 175 
#define  IXGBE_DEV_ID_82598AT 174 
#define  IXGBE_DEV_ID_82598AT2 173 
#define  IXGBE_DEV_ID_82598EB_CX4 172 
#define  IXGBE_DEV_ID_82598EB_SFP_LOM 171 
#define  IXGBE_DEV_ID_82598EB_XF_LR 170 
#define  IXGBE_DEV_ID_82598_BX 169 
#define  IXGBE_DEV_ID_82598_CX4_DUAL_PORT 168 
#define  IXGBE_DEV_ID_82598_DA_DUAL_PORT 167 
#define  IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM 166 
#define  IXGBE_DEV_ID_82599EN_SFP 165 
#define  IXGBE_DEV_ID_82599_BACKPLANE_FCOE 164 
#define  IXGBE_DEV_ID_82599_BYPASS 163 
#define  IXGBE_DEV_ID_82599_COMBO_BACKPLANE 162 
#define  IXGBE_DEV_ID_82599_CX4 161 
#define  IXGBE_DEV_ID_82599_KR 160 
#define  IXGBE_DEV_ID_82599_KX4 159 
#define  IXGBE_DEV_ID_82599_KX4_MEZZ 158 
#define  IXGBE_DEV_ID_82599_QSFP_SF_QP 157 
#define  IXGBE_DEV_ID_82599_SFP 156 
#define  IXGBE_DEV_ID_82599_SFP_EM 155 
#define  IXGBE_DEV_ID_82599_SFP_FCOE 154 
#define  IXGBE_DEV_ID_82599_SFP_SF2 153 
#define  IXGBE_DEV_ID_82599_SFP_SF_QP 152 
#define  IXGBE_DEV_ID_82599_T3_LOM 151 
#define  IXGBE_DEV_ID_82599_XAUI_LOM 150 
#define  IXGBE_DEV_ID_X540T 149 
#define  IXGBE_DEV_ID_X540T1 148 
#define  IXGBE_DEV_ID_X540_BYPASS 147 
#define  IXGBE_DEV_ID_X550EM_A_10G_T 146 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 145 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 144 
#define  IXGBE_DEV_ID_X550EM_A_KR 143 
#define  IXGBE_DEV_ID_X550EM_A_KR_L 142 
#define  IXGBE_DEV_ID_X550EM_A_QSFP 141 
#define  IXGBE_DEV_ID_X550EM_A_QSFP_N 140 
#define  IXGBE_DEV_ID_X550EM_A_SFP 139 
#define  IXGBE_DEV_ID_X550EM_A_SFP_N 138 
#define  IXGBE_DEV_ID_X550EM_A_SGMII 137 
#define  IXGBE_DEV_ID_X550EM_A_SGMII_L 136 
#define  IXGBE_DEV_ID_X550EM_X_10G_T 135 
#define  IXGBE_DEV_ID_X550EM_X_1G_T 134 
#define  IXGBE_DEV_ID_X550EM_X_KR 133 
#define  IXGBE_DEV_ID_X550EM_X_KX4 132 
#define  IXGBE_DEV_ID_X550EM_X_SFP 131 
#define  IXGBE_DEV_ID_X550EM_X_XFI 130 
#define  IXGBE_DEV_ID_X550T 129 
#define  IXGBE_DEV_ID_X550T1 128 
 int /*<<< orphan*/  IXGBE_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  IXGBE_ERR_DEVICE_NOT_SUPPORTED ; 
 scalar_t__ IXGBE_INTEL_VENDOR_ID ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_mac_82598EB ; 
 int /*<<< orphan*/  ixgbe_mac_82599EB ; 
 int /*<<< orphan*/  ixgbe_mac_X540 ; 
 int /*<<< orphan*/  ixgbe_mac_X550 ; 
 int /*<<< orphan*/  ixgbe_mac_X550EM_a ; 
 int /*<<< orphan*/  ixgbe_mac_X550EM_x ; 
 int /*<<< orphan*/  ixgbe_mvals_X540 ; 
 int /*<<< orphan*/  ixgbe_mvals_X550 ; 
 int /*<<< orphan*/  ixgbe_mvals_X550EM_a ; 
 int /*<<< orphan*/  ixgbe_mvals_X550EM_x ; 
 int /*<<< orphan*/  ixgbe_mvals_base ; 

s32 ixgbe_set_mac_type(struct ixgbe_hw *hw)
{
	s32 ret_val = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_set_mac_type\n");

	if (hw->vendor_id != IXGBE_INTEL_VENDOR_ID) {
		ERROR_REPORT2(IXGBE_ERROR_UNSUPPORTED,
			     "Unsupported vendor id: %x", hw->vendor_id);
		return IXGBE_ERR_DEVICE_NOT_SUPPORTED;
	}

	hw->mvals = ixgbe_mvals_base;

	switch (hw->device_id) {
	case IXGBE_DEV_ID_82598:
	case IXGBE_DEV_ID_82598_BX:
	case IXGBE_DEV_ID_82598AF_SINGLE_PORT:
	case IXGBE_DEV_ID_82598AF_DUAL_PORT:
	case IXGBE_DEV_ID_82598AT:
	case IXGBE_DEV_ID_82598AT2:
	case IXGBE_DEV_ID_82598EB_CX4:
	case IXGBE_DEV_ID_82598_CX4_DUAL_PORT:
	case IXGBE_DEV_ID_82598_DA_DUAL_PORT:
	case IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM:
	case IXGBE_DEV_ID_82598EB_XF_LR:
	case IXGBE_DEV_ID_82598EB_SFP_LOM:
		hw->mac.type = ixgbe_mac_82598EB;
		break;
	case IXGBE_DEV_ID_82599_KX4:
	case IXGBE_DEV_ID_82599_KX4_MEZZ:
	case IXGBE_DEV_ID_82599_XAUI_LOM:
	case IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
	case IXGBE_DEV_ID_82599_KR:
	case IXGBE_DEV_ID_82599_SFP:
	case IXGBE_DEV_ID_82599_BACKPLANE_FCOE:
	case IXGBE_DEV_ID_82599_SFP_FCOE:
	case IXGBE_DEV_ID_82599_SFP_EM:
	case IXGBE_DEV_ID_82599_SFP_SF2:
	case IXGBE_DEV_ID_82599_SFP_SF_QP:
	case IXGBE_DEV_ID_82599_QSFP_SF_QP:
	case IXGBE_DEV_ID_82599EN_SFP:
	case IXGBE_DEV_ID_82599_CX4:
	case IXGBE_DEV_ID_82599_BYPASS:
	case IXGBE_DEV_ID_82599_T3_LOM:
		hw->mac.type = ixgbe_mac_82599EB;
		break;
	case IXGBE_DEV_ID_X540T:
	case IXGBE_DEV_ID_X540T1:
	case IXGBE_DEV_ID_X540_BYPASS:
		hw->mac.type = ixgbe_mac_X540;
		hw->mvals = ixgbe_mvals_X540;
		break;
	case IXGBE_DEV_ID_X550T:
	case IXGBE_DEV_ID_X550T1:
		hw->mac.type = ixgbe_mac_X550;
		hw->mvals = ixgbe_mvals_X550;
		break;
	case IXGBE_DEV_ID_X550EM_X_KX4:
	case IXGBE_DEV_ID_X550EM_X_KR:
	case IXGBE_DEV_ID_X550EM_X_10G_T:
	case IXGBE_DEV_ID_X550EM_X_1G_T:
	case IXGBE_DEV_ID_X550EM_X_SFP:
	case IXGBE_DEV_ID_X550EM_X_XFI:
		hw->mac.type = ixgbe_mac_X550EM_x;
		hw->mvals = ixgbe_mvals_X550EM_x;
		break;
	case IXGBE_DEV_ID_X550EM_A_KR:
	case IXGBE_DEV_ID_X550EM_A_KR_L:
	case IXGBE_DEV_ID_X550EM_A_SFP_N:
	case IXGBE_DEV_ID_X550EM_A_SGMII:
	case IXGBE_DEV_ID_X550EM_A_SGMII_L:
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
	case IXGBE_DEV_ID_X550EM_A_10G_T:
	case IXGBE_DEV_ID_X550EM_A_QSFP:
	case IXGBE_DEV_ID_X550EM_A_QSFP_N:
	case IXGBE_DEV_ID_X550EM_A_SFP:
		hw->mac.type = ixgbe_mac_X550EM_a;
		hw->mvals = ixgbe_mvals_X550EM_a;
		break;
	default:
		ret_val = IXGBE_ERR_DEVICE_NOT_SUPPORTED;
		ERROR_REPORT2(IXGBE_ERROR_UNSUPPORTED,
			     "Unsupported device id: %x",
			     hw->device_id);
		break;
	}

	DEBUGOUT2("ixgbe_set_mac_type found mac: %d, returns: %d\n",
		  hw->mac.type, ret_val);
	return ret_val;
}