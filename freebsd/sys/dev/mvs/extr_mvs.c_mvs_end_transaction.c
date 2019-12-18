#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ func_code; int flags; int status; size_t target_id; scalar_t__ recovery_type; int /*<<< orphan*/  path; } ;
struct TYPE_9__ {int flags; } ;
struct ata_res {int dummy; } ;
struct TYPE_10__ {TYPE_2__ cmd; struct ata_res res; } ;
struct TYPE_11__ {int /*<<< orphan*/  scsi_status; scalar_t__ dxfer_len; scalar_t__ resid; } ;
union ccb {TYPE_7__ ccb_h; TYPE_3__ ataio; TYPE_4__ csio; } ;
struct TYPE_13__ {int /*<<< orphan*/  data_map; } ;
struct mvs_slot {int slot; int tag; union ccb* ccb; int /*<<< orphan*/  state; TYPE_6__ dma; int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  data_tag; int /*<<< orphan*/  workrq_map; int /*<<< orphan*/  workrq_tag; } ;
struct mvs_channel {scalar_t__ basic_dma; scalar_t__ numpslots; int eslots; int fatalerr; int oslots; int rslots; int aslots; scalar_t__ numrslots; int* otagspd; int toslots; int* holdtag; int pm_level; int /*<<< orphan*/  pm_timer; scalar_t__ pm_present; TYPE_1__* curr; int /*<<< orphan*/  sim; union ccb* frozen; scalar_t__ numhslots; int /*<<< orphan*/  recoverycmd; union ccb** hold; int /*<<< orphan*/  numdslots; int /*<<< orphan*/ * numtslotspd; int /*<<< orphan*/  numtslots; int /*<<< orphan*/ * numrslotspd; TYPE_5__ dma; scalar_t__ donecount; } ;
typedef  enum mvs_err_type { ____Placeholder_mvs_err_type } mvs_err_type ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CAM_ATAIO_DMA ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int CAM_ATA_STATUS_ERROR ; 
 int CAM_CMD_TIMEOUT ; 
 int CAM_DEV_QFRZN ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int CAM_DIS_AUTOSENSE ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_REQ_INVALID ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_STATUS_MASK ; 
 int CAM_UNCOR_PARITY ; 
 int CTS_SATA_CAPS_D_PMREQ ; 
 int /*<<< orphan*/  MVS_EDMA_OFF ; 
#define  MVS_ERR_INNOCENT 134 
#define  MVS_ERR_INVALID 133 
#define  MVS_ERR_NCQ 132 
#define  MVS_ERR_NONE 131 
#define  MVS_ERR_SATA 130 
#define  MVS_ERR_TFE 129 
#define  MVS_ERR_TIMEOUT 128 
 int /*<<< orphan*/  MVS_SLOT_EMPTY ; 
 scalar_t__ RECOVERY_READ_LOG ; 
 scalar_t__ RECOVERY_REQUEST_SENSE ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_COND ; 
 int /*<<< orphan*/  SCSI_STATUS_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XPT_ATA_IO ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ata_res*,int) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mvs_begin_transaction (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  mvs_check_collision (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  mvs_issue_recovery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_process_read_log (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  mvs_process_request_sense (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  mvs_rearm_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_set_edma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_tfd_read (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_end_transaction(struct mvs_slot *slot, enum mvs_err_type et)
{
	device_t dev = slot->dev;
	struct mvs_channel *ch = device_get_softc(dev);
	union ccb *ccb = slot->ccb;
	int lastto;

	bus_dmamap_sync(ch->dma.workrq_tag, ch->dma.workrq_map,
	    BUS_DMASYNC_POSTWRITE);
	/* Read result registers to the result struct
	 * May be incorrect if several commands finished same time,
	 * so read only when sure or have to.
	 */
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		struct ata_res *res = &ccb->ataio.res;

		if ((et == MVS_ERR_TFE) ||
		    (ccb->ataio.cmd.flags & CAM_ATAIO_NEEDRESULT)) {
			mvs_tfd_read(dev, ccb);
		} else
			bzero(res, sizeof(*res));
	} else {
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE &&
		    ch->basic_dma == 0)
			ccb->csio.resid = ccb->csio.dxfer_len - ch->donecount;
	}
	if (ch->numpslots == 0 || ch->basic_dma) {
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
			bus_dmamap_sync(ch->dma.data_tag, slot->dma.data_map,
			    (ccb->ccb_h.flags & CAM_DIR_IN) ?
			    BUS_DMASYNC_POSTREAD : BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(ch->dma.data_tag, slot->dma.data_map);
		}
	}
	if (et != MVS_ERR_NONE)
		ch->eslots |= (1 << slot->slot);
	/* In case of error, freeze device for proper recovery. */
	if ((et != MVS_ERR_NONE) && (!ch->recoverycmd) &&
	    !(ccb->ccb_h.status & CAM_DEV_QFRZN)) {
		xpt_freeze_devq(ccb->ccb_h.path, 1);
		ccb->ccb_h.status |= CAM_DEV_QFRZN;
	}
	/* Set proper result status. */
	ccb->ccb_h.status &= ~CAM_STATUS_MASK;
	switch (et) {
	case MVS_ERR_NONE:
		ccb->ccb_h.status |= CAM_REQ_CMP;
		if (ccb->ccb_h.func_code == XPT_SCSI_IO)
			ccb->csio.scsi_status = SCSI_STATUS_OK;
		break;
	case MVS_ERR_INVALID:
		ch->fatalerr = 1;
		ccb->ccb_h.status |= CAM_REQ_INVALID;
		break;
	case MVS_ERR_INNOCENT:
		ccb->ccb_h.status |= CAM_REQUEUE_REQ;
		break;
	case MVS_ERR_TFE:
	case MVS_ERR_NCQ:
		if (ccb->ccb_h.func_code == XPT_SCSI_IO) {
			ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
			ccb->csio.scsi_status = SCSI_STATUS_CHECK_COND;
		} else {
			ccb->ccb_h.status |= CAM_ATA_STATUS_ERROR;
		}
		break;
	case MVS_ERR_SATA:
		ch->fatalerr = 1;
		if (!ch->recoverycmd) {
			xpt_freeze_simq(ch->sim, 1);
			ccb->ccb_h.status &= ~CAM_STATUS_MASK;
			ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		}
		ccb->ccb_h.status |= CAM_UNCOR_PARITY;
		break;
	case MVS_ERR_TIMEOUT:
		if (!ch->recoverycmd) {
			xpt_freeze_simq(ch->sim, 1);
			ccb->ccb_h.status &= ~CAM_STATUS_MASK;
			ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		}
		ccb->ccb_h.status |= CAM_CMD_TIMEOUT;
		break;
	default:
		ch->fatalerr = 1;
		ccb->ccb_h.status |= CAM_REQ_CMP_ERR;
	}
	/* Free slot. */
	ch->oslots &= ~(1 << slot->slot);
	ch->rslots &= ~(1 << slot->slot);
	ch->aslots &= ~(1 << slot->slot);
	slot->state = MVS_SLOT_EMPTY;
	slot->ccb = NULL;
	/* Update channel stats. */
	ch->numrslots--;
	ch->numrslotspd[ccb->ccb_h.target_id]--;
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		if (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA) {
			ch->otagspd[ccb->ccb_h.target_id] &= ~(1 << slot->tag);
			ch->numtslots--;
			ch->numtslotspd[ccb->ccb_h.target_id]--;
		} else if (ccb->ataio.cmd.flags & CAM_ATAIO_DMA) {
			ch->numdslots--;
		} else {
			ch->numpslots--;
		}
	} else {
		ch->numpslots--;
		ch->basic_dma = 0;
	}
	/* Cancel timeout state if request completed normally. */
	if (et != MVS_ERR_TIMEOUT) {
		lastto = (ch->toslots == (1 << slot->slot));
		ch->toslots &= ~(1 << slot->slot);
		if (lastto)
			xpt_release_simq(ch->sim, TRUE);
	}
	/* If it was our READ LOG command - process it. */
	if (ccb->ccb_h.recovery_type == RECOVERY_READ_LOG) {
		mvs_process_read_log(dev, ccb);
	/* If it was our REQUEST SENSE command - process it. */
	} else if (ccb->ccb_h.recovery_type == RECOVERY_REQUEST_SENSE) {
		mvs_process_request_sense(dev, ccb);
	/* If it was NCQ or ATAPI command error, put result on hold. */
	} else if (et == MVS_ERR_NCQ ||
	    ((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_SCSI_STATUS_ERROR &&
	     (ccb->ccb_h.flags & CAM_DIS_AUTOSENSE) == 0)) {
		ch->hold[slot->slot] = ccb;
		ch->holdtag[slot->slot] = slot->tag;
		ch->numhslots++;
	} else
		xpt_done(ccb);
	/* If we have no other active commands, ... */
	if (ch->rslots == 0) {
		/* if there was fatal error - reset port. */
		if (ch->toslots != 0 || ch->fatalerr) {
			mvs_reset(dev);
		} else {
			/* if we have slots in error, we can reinit port. */
			if (ch->eslots != 0) {
				mvs_set_edma_mode(dev, MVS_EDMA_OFF);
				ch->eslots = 0;
			}
			/* if there commands on hold, we can do READ LOG. */
			if (!ch->recoverycmd && ch->numhslots)
				mvs_issue_recovery(dev);
		}
	/* If all the rest of commands are in timeout - give them chance. */
	} else if ((ch->rslots & ~ch->toslots) == 0 &&
	    et != MVS_ERR_TIMEOUT)
		mvs_rearm_timeout(dev);
	/* Unfreeze frozen command. */
	if (ch->frozen && !mvs_check_collision(dev, ch->frozen)) {
		union ccb *fccb = ch->frozen;
		ch->frozen = NULL;
		mvs_begin_transaction(dev, fccb);
		xpt_release_simq(ch->sim, TRUE);
	}
	/* Start PM timer. */
	if (ch->numrslots == 0 && ch->pm_level > 3 &&
	    (ch->curr[ch->pm_present ? 15 : 0].caps & CTS_SATA_CAPS_D_PMREQ)) {
		callout_schedule(&ch->pm_timer,
		    (ch->pm_level == 4) ? hz / 1000 : hz / 8);
	}
}