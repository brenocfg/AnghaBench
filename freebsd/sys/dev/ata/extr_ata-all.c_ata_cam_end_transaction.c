#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int status; scalar_t__ func_code; int flags; int /*<<< orphan*/  path; } ;
struct TYPE_11__ {scalar_t__ dxfer_len; scalar_t__ resid; int /*<<< orphan*/  scsi_status; } ;
struct ata_res {int status; int lba_low; int lba_mid; int lba_high; int device; int lba_low_exp; int lba_mid_exp; int lba_high_exp; int sector_count; int sector_count_exp; int /*<<< orphan*/  error; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_10__ {scalar_t__ dxfer_len; scalar_t__ resid; struct ata_res res; TYPE_1__ cmd; } ;
union ccb {TYPE_6__ ccb_h; TYPE_5__ csio; TYPE_4__ ataio; } ;
struct TYPE_8__ {int lba; int count; } ;
struct TYPE_9__ {TYPE_2__ ata; } ;
struct ata_request {int flags; int status; scalar_t__ result; scalar_t__ donecount; TYPE_3__ u; int /*<<< orphan*/  error; union ccb* ccb; } ;
struct ata_channel {int /*<<< orphan*/  sim; scalar_t__ requestsense; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_R_TIMEOUT ; 
 int ATA_S_ERROR ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int CAM_ATA_STATUS_ERROR ; 
 int CAM_CMD_TIMEOUT ; 
 int CAM_DEV_QFRZN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int CAM_DIS_AUTOSENSE ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_STATUS_MASK ; 
 scalar_t__ ERESTART ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_COND ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  ata_cam_process_sense (int /*<<< orphan*/ ,struct ata_request*) ; 
 int /*<<< orphan*/  ata_cam_request_sense (int /*<<< orphan*/ ,struct ata_request*) ; 
 int /*<<< orphan*/  ata_reinit (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ata_cam_end_transaction(device_t dev, struct ata_request *request)
{
	struct ata_channel *ch = device_get_softc(dev);
	union ccb *ccb = request->ccb;
	int fatalerr = 0;

	if (ch->requestsense) {
		ata_cam_process_sense(dev, request);
		return;
	}

	ccb->ccb_h.status &= ~CAM_STATUS_MASK;
	if (request->flags & ATA_R_TIMEOUT) {
		xpt_freeze_simq(ch->sim, 1);
		ccb->ccb_h.status &= ~CAM_STATUS_MASK;
		ccb->ccb_h.status |= CAM_CMD_TIMEOUT | CAM_RELEASE_SIMQ;
		fatalerr = 1;
	} else if (request->status & ATA_S_ERROR) {
		if (ccb->ccb_h.func_code == XPT_ATA_IO) {
			ccb->ccb_h.status |= CAM_ATA_STATUS_ERROR;
		} else {
			ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
			ccb->csio.scsi_status = SCSI_STATUS_CHECK_COND;
		}
	} else if (request->result == ERESTART)
		ccb->ccb_h.status |= CAM_REQUEUE_REQ;
	else if (request->result != 0)
		ccb->ccb_h.status |= CAM_REQ_CMP_ERR;
	else
		ccb->ccb_h.status |= CAM_REQ_CMP;
	if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP &&
	    !(ccb->ccb_h.status & CAM_DEV_QFRZN)) {
		xpt_freeze_devq(ccb->ccb_h.path, 1);
		ccb->ccb_h.status |= CAM_DEV_QFRZN;
	}
	if (ccb->ccb_h.func_code == XPT_ATA_IO &&
	    ((request->status & ATA_S_ERROR) ||
	    (ccb->ataio.cmd.flags & CAM_ATAIO_NEEDRESULT))) {
		struct ata_res *res = &ccb->ataio.res;
		res->status = request->status;
		res->error = request->error;
		res->lba_low = request->u.ata.lba;
		res->lba_mid = request->u.ata.lba >> 8;
		res->lba_high = request->u.ata.lba >> 16;
		res->device = request->u.ata.lba >> 24;
		res->lba_low_exp = request->u.ata.lba >> 24;
		res->lba_mid_exp = request->u.ata.lba >> 32;
		res->lba_high_exp = request->u.ata.lba >> 40;
		res->sector_count = request->u.ata.count;
		res->sector_count_exp = request->u.ata.count >> 8;
	}
	if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		if (ccb->ccb_h.func_code == XPT_ATA_IO) {
			ccb->ataio.resid =
			    ccb->ataio.dxfer_len - request->donecount;
		} else {
			ccb->csio.resid =
			    ccb->csio.dxfer_len - request->donecount;
		}
	}
	if ((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_SCSI_STATUS_ERROR &&
	    (ccb->ccb_h.flags & CAM_DIS_AUTOSENSE) == 0)
		ata_cam_request_sense(dev, request);
	else
		xpt_done(ccb);
	/* Do error recovery if needed. */
	if (fatalerr)
		ata_reinit(dev);
}