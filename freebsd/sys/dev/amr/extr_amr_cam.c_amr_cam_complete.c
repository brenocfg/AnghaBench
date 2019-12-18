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
typedef  union ccb {int dummy; } ccb ;
struct scsi_inquiry_data {int device; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  status; } ;
struct ccb_scsiio {scalar_t__ data_ptr; int /*<<< orphan*/  dxfer_len; TYPE_3__ ccb_h; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; int /*<<< orphan*/  scsi_status; } ;
struct amr_passthrough {int ap_scsi_status; int* ap_cdb; int /*<<< orphan*/  ap_request_sense_area; } ;
struct amr_ext_passthrough {int ap_scsi_status; int* ap_cdb; int /*<<< orphan*/  ap_request_sense_area; } ;
struct TYPE_6__ {scalar_t__ mb_command; } ;
struct amr_command {scalar_t__ ac_status; TYPE_4__* ac_sc; TYPE_2__ ac_mailbox; scalar_t__ ac_private; TYPE_1__* ac_ccb; } ;
struct TYPE_8__ {int /*<<< orphan*/  amr_list_lock; } ;
struct TYPE_5__ {struct amr_ext_passthrough ccb_epthru; struct amr_passthrough ccb_pthru; } ;

/* Variables and functions */
 scalar_t__ AMR_CMD_EXTPASS ; 
 int /*<<< orphan*/  AMR_MAX_REQ_SENSE_LEN ; 
 scalar_t__ AMR_STATUS_SUCCESS ; 
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_BUSY ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
 int /*<<< orphan*/  CAM_SEL_TIMEOUT ; 
 int INQUIRY ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_COND ; 
 int /*<<< orphan*/  SID_TYPE (struct scsi_inquiry_data*) ; 
 int /*<<< orphan*/  T_DIRECT ; 
 int T_NODEVICE ; 
 int /*<<< orphan*/  amr_releasecmd (struct amr_command*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int,char*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  imin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
amr_cam_complete(struct amr_command *ac)
{
	struct amr_passthrough		*ap;
	struct amr_ext_passthrough	*aep;
	struct ccb_scsiio		*csio;
	struct scsi_inquiry_data	*inq;
	int				scsi_status, cdb0;

	ap = &ac->ac_ccb->ccb_pthru;
	aep = &ac->ac_ccb->ccb_epthru;
	csio = (struct ccb_scsiio *)ac->ac_private;
	inq = (struct scsi_inquiry_data *)csio->data_ptr;

	if (ac->ac_mailbox.mb_command == AMR_CMD_EXTPASS)
		scsi_status = aep->ap_scsi_status;
	else
		scsi_status = ap->ap_scsi_status;
	debug(1, "status 0x%x  AP scsi_status 0x%x", ac->ac_status,
	    scsi_status);

	/* Make sure the status is sane */
	if ((ac->ac_status != AMR_STATUS_SUCCESS) && (scsi_status == 0)) {
		csio->ccb_h.status = CAM_REQ_CMP_ERR;
		goto out;
	}

	/*
	 * Hide disks from CAM so that they're not picked up and treated as
	 * 'normal' disks.
	 *
	 * If the configuration provides a mechanism to mark a disk a "not
	 * managed", we could add handling for that to allow disks to be
	 * selectively visible.
	 */

	/* handle passthrough SCSI status */
	switch(scsi_status) {
	case 0:	/* completed OK */
		if (ac->ac_mailbox.mb_command == AMR_CMD_EXTPASS)
			cdb0 = aep->ap_cdb[0];
		else
			cdb0 = ap->ap_cdb[0];
		if ((cdb0 == INQUIRY) && (SID_TYPE(inq) == T_DIRECT))
			inq->device = (inq->device & 0xe0) | T_NODEVICE;
		csio->ccb_h.status = CAM_REQ_CMP;
		break;

	case 0x02:
		csio->ccb_h.status = CAM_SCSI_STATUS_ERROR;
		csio->scsi_status = SCSI_STATUS_CHECK_COND;
		if (ac->ac_mailbox.mb_command == AMR_CMD_EXTPASS)
			bcopy(aep->ap_request_sense_area, &csio->sense_data,
			    AMR_MAX_REQ_SENSE_LEN);
		else
			bcopy(ap->ap_request_sense_area, &csio->sense_data,
			    AMR_MAX_REQ_SENSE_LEN);
		csio->sense_len = AMR_MAX_REQ_SENSE_LEN;
		csio->ccb_h.status |= CAM_AUTOSNS_VALID;
		break;

	case 0x08:
		csio->ccb_h.status = CAM_SCSI_BUSY;
		break;

	case 0xf0:
	case 0xf4:
	default:
		/*
		 * Non-zero LUNs are already filtered, so there's no need
		 * to return CAM_DEV_NOT_THERE.
		 */
		csio->ccb_h.status = CAM_SEL_TIMEOUT;
		break;
	}

out:
	if ((csio->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE)
		debug(2, "%*D\n", imin(csio->dxfer_len, 16), csio->data_ptr,
		    " ");

	mtx_lock(&ac->ac_sc->amr_list_lock);
	xpt_done((union ccb *)csio);
	amr_releasecmd(ac);
	mtx_unlock(&ac->ac_sc->amr_list_lock);
}