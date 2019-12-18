#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  hw; TYPE_2__* domain; } ;
typedef  TYPE_3__ ocs_t ;
typedef  int ocs_scsi_property_e ;
struct TYPE_9__ {TYPE_1__* sport; } ;
struct TYPE_8__ {int /*<<< orphan*/ * wwnn_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_BIOS_VERSION_STRING ; 
 int /*<<< orphan*/  OCS_HW_PORTNUM ; 
 int /*<<< orphan*/  OCS_HW_VPD ; 
 int /*<<< orphan*/  OCS_HW_VPD_LEN ; 
 int /*<<< orphan*/  OCS_HW_WWN_NODE ; 
 int /*<<< orphan*/  OCS_HW_WWN_PORT ; 
#define  OCS_SCSI_BIOS_VERSION_STRING 133 
#define  OCS_SCSI_PARTNUMBER 132 
#define  OCS_SCSI_PORTNUM 131 
#define  OCS_SCSI_SERIALNUMBER 130 
#define  OCS_SCSI_WWNN 129 
#define  OCS_SCSI_WWPN 128 
 void* ocs_find_vpd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_hw_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ocs_hw_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  ocs_strlen (void*) ; 
 int /*<<< orphan*/  scsi_log (TYPE_3__*,char*) ; 

void *ocs_scsi_get_property_ptr(ocs_t *ocs, ocs_scsi_property_e prop)
{
	void *rc = NULL;

	switch (prop) {
	case OCS_SCSI_WWNN:
		rc = ocs_hw_get_ptr(&ocs->hw, OCS_HW_WWN_NODE);
		break;
	case OCS_SCSI_WWPN:
		rc = ocs_hw_get_ptr(&ocs->hw, OCS_HW_WWN_PORT);
		break;
	case OCS_SCSI_PORTNUM:
		rc = ocs_hw_get_ptr(&ocs->hw, OCS_HW_PORTNUM);
		break;
	case OCS_SCSI_BIOS_VERSION_STRING:
		rc = ocs_hw_get_ptr(&ocs->hw, OCS_HW_BIOS_VERSION_STRING);
		break;
#if defined(OCS_ENABLE_VPD_SUPPORT)
	case OCS_SCSI_SERIALNUMBER:
	{
		uint8_t *pvpd;
		uint32_t vpd_len;

		if (ocs_hw_get(&ocs->hw, OCS_HW_VPD_LEN, &vpd_len)) {
			ocs_log_test(ocs, "Can't get VPD length\n");
			rc = "\012sn-unknown";
			break;
		}

		pvpd = ocs_hw_get_ptr(&ocs->hw, OCS_HW_VPD);
		if (pvpd) {
			rc = ocs_find_vpd(pvpd, vpd_len, "SN");
		}

		if (rc == NULL ||
		    ocs_strlen(rc) == 0) {
			/* Note: VPD is missing, using wwnn for serial number */
			scsi_log(ocs, "Note: VPD is missing, using wwnn for serial number\n");
			/* Use the last 32 bits of the WWN */
			if ((ocs == NULL) || (ocs->domain == NULL) || (ocs->domain->sport == NULL)) {
				rc = "\011(Unknown)";
			} else {
				rc = &ocs->domain->sport->wwnn_str[8];
			}
		}
		break;
	}
	case OCS_SCSI_PARTNUMBER:
	{
		uint8_t *pvpd;
		uint32_t vpd_len;

		if (ocs_hw_get(&ocs->hw, OCS_HW_VPD_LEN, &vpd_len)) {
			ocs_log_test(ocs, "Can't get VPD length\n");
			rc = "\012pn-unknown";
			break;
		}
		pvpd = ocs_hw_get_ptr(&ocs->hw, OCS_HW_VPD);
		if (pvpd) {
			rc = ocs_find_vpd(pvpd, vpd_len, "PN");
			if (rc == NULL) {
				rc = "\012pn-unknown";
			}
		} else {
			rc = "\012pn-unknown";
		}
		break;
	}
#endif
	default:
		break;
	}

	if (rc == NULL) {
		ocs_log_debug(ocs, "invalid property request %d\n", prop);
	}
	return rc;
}