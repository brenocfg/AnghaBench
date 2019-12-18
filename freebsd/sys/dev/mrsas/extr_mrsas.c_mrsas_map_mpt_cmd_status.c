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
struct TYPE_4__ {int sense_len; int scsi_status; int /*<<< orphan*/  sense_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  target_lun; } ;
union ccb {TYPE_2__ csio; TYPE_1__ ccb_h; } ;
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; } ;
struct mrsas_mpt_cmd {struct mrsas_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_DEV_NOT_THERE ; 
 int /*<<< orphan*/  CAM_LUN_INVALID ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
#define  MFI_STAT_CONFIG_SEQ_MISMATCH 133 
#define  MFI_STAT_DEVICE_NOT_FOUND 132 
#define  MFI_STAT_LD_OFFLINE 131 
#define  MFI_STAT_OK 130 
#define  MFI_STAT_SCSI_DONE_WITH_ERROR 129 
#define  MFI_STAT_SCSI_IO_FAILED 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void
mrsas_map_mpt_cmd_status(struct mrsas_mpt_cmd *cmd, union ccb *ccb_ptr, u_int8_t status,
    u_int8_t extStatus, u_int32_t data_length, u_int8_t *sense)
{
	struct mrsas_softc *sc = cmd->sc;
	u_int8_t *sense_data;

	switch (status) {
	case MFI_STAT_OK:
		ccb_ptr->ccb_h.status = CAM_REQ_CMP;
		break;
	case MFI_STAT_SCSI_IO_FAILED:
	case MFI_STAT_SCSI_DONE_WITH_ERROR:
		ccb_ptr->ccb_h.status = CAM_SCSI_STATUS_ERROR;
		sense_data = (u_int8_t *)&ccb_ptr->csio.sense_data;
		if (sense_data) {
			/* For now just copy 18 bytes back */
			memcpy(sense_data, sense, 18);
			ccb_ptr->csio.sense_len = 18;
			ccb_ptr->ccb_h.status |= CAM_AUTOSNS_VALID;
		}
		break;
	case MFI_STAT_LD_OFFLINE:
	case MFI_STAT_DEVICE_NOT_FOUND:
		if (ccb_ptr->ccb_h.target_lun)
			ccb_ptr->ccb_h.status |= CAM_LUN_INVALID;
		else
			ccb_ptr->ccb_h.status |= CAM_DEV_NOT_THERE;
		break;
	case MFI_STAT_CONFIG_SEQ_MISMATCH:
		ccb_ptr->ccb_h.status |= CAM_REQUEUE_REQ;
		break;
	default:
		device_printf(sc->mrsas_dev, "FW cmd complete status %x\n", status);
		ccb_ptr->ccb_h.status = CAM_REQ_CMP_ERR;
		ccb_ptr->csio.scsi_status = status;
	}
	return;
}