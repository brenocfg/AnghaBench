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
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_3__ {int volume_status; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DISC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
#define  SA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER 140 
#define  SA_LV_ENCRYPTED_NO_KEY 139 
#define  SA_LV_NOT_AVAILABLE 138 
#define  SA_LV_OK 137 
#define  SA_LV_PENDING_ENCRYPTION 136 
#define  SA_LV_PENDING_ENCRYPTION_REKEYING 135 
#define  SA_LV_PENDING_RPI 134 
#define  SA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER 133 
#define  SA_LV_STATUS_VPD_UNSUPPORTED 132 
#define  SA_LV_UNDERGOING_ENCRYPTION 131 
#define  SA_LV_UNDERGOING_ENCRYPTION_REKEYING 130 
#define  SA_LV_UNDERGOING_ERASE 129 
#define  SA_LV_UNDERGOING_RPI 128 

__attribute__((used)) static void pqisrc_display_volume_status(pqisrc_softstate_t *softs,
	pqi_scsi_dev_t *device)
{
	char *status;

	DBG_FUNC("IN\n");
	switch (device->volume_status) {
	case SA_LV_OK:
		status = "Volume is online.";
		break;
	case SA_LV_UNDERGOING_ERASE:
		status = "Volume is undergoing background erase process.";
		break;
	case SA_LV_NOT_AVAILABLE:
		status = "Volume is waiting for transforming volume.";
		break;
	case SA_LV_UNDERGOING_RPI:
		status = "Volume is undergoing rapid parity initialization process.";
		break;
	case SA_LV_PENDING_RPI:
		status = "Volume is queued for rapid parity initialization process.";
		break;
	case SA_LV_ENCRYPTED_NO_KEY:
		status = "Volume is encrypted and cannot be accessed because key is not present.";
		break;
	case SA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER:
		status = "Volume is not encrypted and cannot be accessed because controller is in encryption-only mode.";
		break;
	case SA_LV_UNDERGOING_ENCRYPTION:
		status = "Volume is undergoing encryption process.";
		break;
	case SA_LV_UNDERGOING_ENCRYPTION_REKEYING:
		status = "Volume is undergoing encryption re-keying process.";
		break;
	case SA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		status = "Volume is encrypted and cannot be accessed because controller does not have encryption enabled.";
		break;
	case SA_LV_PENDING_ENCRYPTION:
		status = "Volume is pending migration to encrypted state, but process has not started.";
		break;
	case SA_LV_PENDING_ENCRYPTION_REKEYING:
		status = "Volume is encrypted and is pending encryption rekeying.";
		break;
	case SA_LV_STATUS_VPD_UNSUPPORTED:
		status = "Volume status is not available through vital product data pages.";
		break;
	default:
		status = "Volume is in an unknown state.";
		break;
	}

	DBG_DISC("scsi BTL %d:%d:%d %s\n",
		device->bus, device->target, device->lun, status);
	DBG_FUNC("OUT\n");
}