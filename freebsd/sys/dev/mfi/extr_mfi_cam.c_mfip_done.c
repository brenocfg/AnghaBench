#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* cdb_ptr; int* cdb_bytes; } ;
struct ccb_scsiio {int* data_ptr; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_data; scalar_t__ sense_resid; scalar_t__ sense_len; TYPE_2__ cdb_io; } ;
struct ccb_hdr {int status; int flags; struct mfip_softc* ccb_mfip_ptr; } ;
union ccb {struct ccb_scsiio csio; struct ccb_hdr ccb_h; } ;
typedef  int uint8_t ;
struct scsi_sense_data {int dummy; } ;
struct mfip_softc {int dummy; } ;
struct TYPE_8__ {int cmd_status; int /*<<< orphan*/  scsi_status; scalar_t__ sense_len; } ;
struct mfi_pass_frame {TYPE_4__ header; } ;
struct mfi_command {TYPE_3__* cm_sense; TYPE_1__* cm_frame; union ccb* cm_private; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {struct mfi_pass_frame pass; } ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
 int CAM_CDB_POINTER ; 
 int CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_SEL_TIMEOUT ; 
 int INQUIRY ; 
#define  MFI_STAT_DEVICE_NOT_FOUND 131 
#define  MFI_STAT_OK 130 
#define  MFI_STAT_SCSI_DONE_WITH_ERROR 129 
#define  MFI_STAT_SCSI_IO_FAILED 128 
 int T_DIRECT ; 
 int T_NODEVICE ; 
 int T_PROCESSOR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mfi_allow_disks ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
mfip_done(struct mfi_command *cm)
{
	union ccb *ccb = cm->cm_private;
	struct ccb_hdr *ccbh = &ccb->ccb_h;
	struct ccb_scsiio *csio = &ccb->csio;
	struct mfip_softc *sc;
	struct mfi_pass_frame *pt;

	sc = ccbh->ccb_mfip_ptr;
	pt = &cm->cm_frame->pass;

	switch (pt->header.cmd_status) {
	case MFI_STAT_OK:
	{
		uint8_t command, device;

		ccbh->status = CAM_REQ_CMP;
		csio->scsi_status = pt->header.scsi_status;
		if (ccbh->flags & CAM_CDB_POINTER)
			command = csio->cdb_io.cdb_ptr[0];
		else
			command = csio->cdb_io.cdb_bytes[0];
		if (command == INQUIRY) {
			device = csio->data_ptr[0] & 0x1f;
			if ((!mfi_allow_disks && device == T_DIRECT) ||
			    (device == T_PROCESSOR))
				csio->data_ptr[0] =
				     (csio->data_ptr[0] & 0xe0) | T_NODEVICE;
		}
		break;
	}
	case MFI_STAT_SCSI_DONE_WITH_ERROR:
	{
		int sense_len;

		ccbh->status = CAM_SCSI_STATUS_ERROR | CAM_AUTOSNS_VALID;
		csio->scsi_status = pt->header.scsi_status;
		if (pt->header.sense_len < csio->sense_len)
			csio->sense_resid = csio->sense_len -
			    pt->header.sense_len;
		else
			csio->sense_resid = 0;
		sense_len = min(pt->header.sense_len,
		    sizeof(struct scsi_sense_data));
		bzero(&csio->sense_data, sizeof(struct scsi_sense_data));
		bcopy(&cm->cm_sense->data[0], &csio->sense_data, sense_len);
		break;
	}
	case MFI_STAT_DEVICE_NOT_FOUND:
		ccbh->status = CAM_SEL_TIMEOUT;
		break;
	case MFI_STAT_SCSI_IO_FAILED:
		ccbh->status = CAM_REQ_CMP_ERR;
		csio->scsi_status = pt->header.scsi_status;
		break;
	default:
		ccbh->status = CAM_REQ_CMP_ERR;
		csio->scsi_status = pt->header.scsi_status;
		break;
	}

	mfi_release_command(cm);
	xpt_done(ccb);
}