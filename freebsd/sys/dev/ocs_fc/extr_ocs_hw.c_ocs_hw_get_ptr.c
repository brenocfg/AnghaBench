#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int ocs_hw_property_e ;

/* Variables and functions */
#define  OCS_HW_BIOS_VERSION_STRING 135 
#define  OCS_HW_FW_REV 134 
#define  OCS_HW_FW_REV2 133 
#define  OCS_HW_IPL 132 
#define  OCS_HW_PORTNUM 131 
#define  OCS_HW_VPD 130 
#define  OCS_HW_WWN_NODE 129 
#define  OCS_HW_WWN_PORT 128 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 void* sli_get_bios_version_string (int /*<<< orphan*/ *) ; 
 void* sli_get_fw_name (int /*<<< orphan*/ *,int) ; 
 void* sli_get_ipl_name (int /*<<< orphan*/ *) ; 
 void* sli_get_portnum (int /*<<< orphan*/ *) ; 
 void* sli_get_vpd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_get_vpd_len (int /*<<< orphan*/ *) ; 
 void* sli_get_wwn_node (int /*<<< orphan*/ *) ; 
 void* sli_get_wwn_port (int /*<<< orphan*/ *) ; 

void *
ocs_hw_get_ptr(ocs_hw_t *hw, ocs_hw_property_e prop)
{
	void	*rc = NULL;

	switch (prop) {
	case OCS_HW_WWN_NODE:
		rc = sli_get_wwn_node(&hw->sli);
		break;
	case OCS_HW_WWN_PORT:
		rc = sli_get_wwn_port(&hw->sli);
		break;
	case OCS_HW_VPD:
		/* make sure VPD length is non-zero */
		if (sli_get_vpd_len(&hw->sli)) {
			rc = sli_get_vpd(&hw->sli);
		}
		break;
	case OCS_HW_FW_REV:
		rc = sli_get_fw_name(&hw->sli, 0);
		break;
	case OCS_HW_FW_REV2:
		rc = sli_get_fw_name(&hw->sli, 1);
		break;
	case OCS_HW_IPL:
		rc = sli_get_ipl_name(&hw->sli);
		break;
	case OCS_HW_PORTNUM:
		rc = sli_get_portnum(&hw->sli);
		break;
	case OCS_HW_BIOS_VERSION_STRING:
		rc = sli_get_bios_version_string(&hw->sli);
		break;
	default:
		ocs_log_test(hw->os, "unsupported property %#x\n", prop);
	}

	return rc;
}