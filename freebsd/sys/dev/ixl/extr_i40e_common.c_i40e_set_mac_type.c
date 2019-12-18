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
struct i40e_hw {scalar_t__ vendor_id; int device_id; TYPE_1__ mac; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT2 (char*,int /*<<< orphan*/ ,int) ; 
#define  I40E_DEV_ID_10G_BASE_T 150 
#define  I40E_DEV_ID_10G_BASE_T4 149 
#define  I40E_DEV_ID_10G_BASE_T_X722 148 
#define  I40E_DEV_ID_1G_BASE_T_X722 147 
#define  I40E_DEV_ID_20G_KR2 146 
#define  I40E_DEV_ID_20G_KR2_A 145 
#define  I40E_DEV_ID_25G_B 144 
#define  I40E_DEV_ID_25G_SFP28 143 
#define  I40E_DEV_ID_ADAPTIVE_VF 142 
#define  I40E_DEV_ID_KX_B 141 
#define  I40E_DEV_ID_KX_C 140 
#define  I40E_DEV_ID_KX_X722 139 
#define  I40E_DEV_ID_QEMU 138 
#define  I40E_DEV_ID_QSFP_A 137 
#define  I40E_DEV_ID_QSFP_B 136 
#define  I40E_DEV_ID_QSFP_C 135 
#define  I40E_DEV_ID_QSFP_X722 134 
#define  I40E_DEV_ID_SFP_I_X722 133 
#define  I40E_DEV_ID_SFP_X722 132 
#define  I40E_DEV_ID_SFP_XL710 131 
#define  I40E_DEV_ID_VF 130 
#define  I40E_DEV_ID_VF_HV 129 
#define  I40E_DEV_ID_X722_VF 128 
 int I40E_ERR_DEVICE_NOT_SUPPORTED ; 
 scalar_t__ I40E_INTEL_VENDOR_ID ; 
 int /*<<< orphan*/  I40E_MAC_GENERIC ; 
 int /*<<< orphan*/  I40E_MAC_VF ; 
 int /*<<< orphan*/  I40E_MAC_X722 ; 
 int /*<<< orphan*/  I40E_MAC_X722_VF ; 
 int /*<<< orphan*/  I40E_MAC_XL710 ; 
 int I40E_SUCCESS ; 

enum i40e_status_code i40e_set_mac_type(struct i40e_hw *hw)
{
	enum i40e_status_code status = I40E_SUCCESS;

	DEBUGFUNC("i40e_set_mac_type\n");

	if (hw->vendor_id == I40E_INTEL_VENDOR_ID) {
		switch (hw->device_id) {
		case I40E_DEV_ID_SFP_XL710:
		case I40E_DEV_ID_QEMU:
		case I40E_DEV_ID_KX_B:
		case I40E_DEV_ID_KX_C:
		case I40E_DEV_ID_QSFP_A:
		case I40E_DEV_ID_QSFP_B:
		case I40E_DEV_ID_QSFP_C:
		case I40E_DEV_ID_10G_BASE_T:
		case I40E_DEV_ID_10G_BASE_T4:
		case I40E_DEV_ID_20G_KR2:
		case I40E_DEV_ID_20G_KR2_A:
		case I40E_DEV_ID_25G_B:
		case I40E_DEV_ID_25G_SFP28:
			hw->mac.type = I40E_MAC_XL710;
			break;
		case I40E_DEV_ID_KX_X722:
		case I40E_DEV_ID_QSFP_X722:
		case I40E_DEV_ID_SFP_X722:
		case I40E_DEV_ID_1G_BASE_T_X722:
		case I40E_DEV_ID_10G_BASE_T_X722:
		case I40E_DEV_ID_SFP_I_X722:
			hw->mac.type = I40E_MAC_X722;
			break;
		case I40E_DEV_ID_X722_VF:
			hw->mac.type = I40E_MAC_X722_VF;
			break;
		case I40E_DEV_ID_VF:
		case I40E_DEV_ID_VF_HV:
		case I40E_DEV_ID_ADAPTIVE_VF:
			hw->mac.type = I40E_MAC_VF;
			break;
		default:
			hw->mac.type = I40E_MAC_GENERIC;
			break;
		}
	} else {
		status = I40E_ERR_DEVICE_NOT_SUPPORTED;
	}

	DEBUGOUT2("i40e_set_mac_type found mac: %d, returns: %d\n",
		  hw->mac.type, status);
	return status;
}