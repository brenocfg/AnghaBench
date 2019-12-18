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
struct TYPE_10__ {scalar_t__ func_code; int flags; int status; size_t target_id; scalar_t__ recovery_type; int /*<<< orphan*/  path; } ;
struct TYPE_11__ {int flags; } ;
struct ata_res {void* sector_count_exp; void* sector_count; void* lba_high_exp; void* lba_mid_exp; void* lba_low_exp; void* device; void* lba_high; void* lba_mid; void* lba_low; void* error; void* status; } ;
struct TYPE_12__ {void* dxfer_len; TYPE_5__ cmd; void* resid; struct ata_res res; } ;
struct TYPE_8__ {void* dxfer_len; int /*<<< orphan*/  scsi_status; void* resid; } ;
union ccb {TYPE_4__ ccb_h; TYPE_6__ ataio; TYPE_2__ csio; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_map; } ;
struct siis_slot {int slot; union ccb* ccb; int /*<<< orphan*/  state; TYPE_1__ dma; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_tag; int /*<<< orphan*/  work_map; int /*<<< orphan*/  work_tag; } ;
struct siis_channel {int numrslots; int eslots; int fatalerr; int oslots; int rslots; int aslots; int toslots; int /*<<< orphan*/  sim; union ccb* frozen; scalar_t__ numhslots; int /*<<< orphan*/  recoverycmd; union ccb** hold; int /*<<< orphan*/ * numtslots; scalar_t__ recovery; TYPE_3__ dma; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  mtx; } ;
typedef  enum siis_err_type { ____Placeholder_siis_err_type } siis_err_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* ATA_INB (int /*<<< orphan*/ ,int) ; 
 void* ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
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
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ RECOVERY_READ_LOG ; 
 scalar_t__ RECOVERY_REQUEST_SENSE ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_COND ; 
 int /*<<< orphan*/  SCSI_STATUS_OK ; 
#define  SIIS_ERR_INNOCENT 134 
#define  SIIS_ERR_INVALID 133 
#define  SIIS_ERR_NCQ 132 
#define  SIIS_ERR_NONE 131 
#define  SIIS_ERR_SATA 130 
#define  SIIS_ERR_TFE 129 
#define  SIIS_ERR_TIMEOUT 128 
 int SIIS_P_LRAM_SLOT (int) ; 
 int /*<<< orphan*/  SIIS_SLOT_EMPTY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XPT_ATA_IO ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ata_res*,int) ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_begin_transaction (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_check_collision (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_issue_recovery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_portinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_process_read_log (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_process_request_sense (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_rearm_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
siis_end_transaction(struct siis_slot *slot, enum siis_err_type et)
{
	device_t dev = slot->dev;
	struct siis_channel *ch = device_get_softc(dev);
	union ccb *ccb = slot->ccb;
	int lastto;

	mtx_assert(&ch->mtx, MA_OWNED);
	bus_dmamap_sync(ch->dma.work_tag, ch->dma.work_map,
	    BUS_DMASYNC_POSTWRITE);
	/* Read result registers to the result struct
	 * May be incorrect if several commands finished same time,
	 * so read only when sure or have to.
	 */
	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		struct ata_res *res = &ccb->ataio.res;
		if ((et == SIIS_ERR_TFE) ||
		    (ccb->ataio.cmd.flags & CAM_ATAIO_NEEDRESULT)) {
			int offs = SIIS_P_LRAM_SLOT(slot->slot) + 8;

			res->status = ATA_INB(ch->r_mem, offs + 2);
			res->error = ATA_INB(ch->r_mem, offs + 3);
			res->lba_low = ATA_INB(ch->r_mem, offs + 4);
			res->lba_mid = ATA_INB(ch->r_mem, offs + 5);
			res->lba_high = ATA_INB(ch->r_mem, offs + 6);
			res->device = ATA_INB(ch->r_mem, offs + 7);
			res->lba_low_exp = ATA_INB(ch->r_mem, offs + 8);
			res->lba_mid_exp = ATA_INB(ch->r_mem, offs + 9);
			res->lba_high_exp = ATA_INB(ch->r_mem, offs + 10);
			res->sector_count = ATA_INB(ch->r_mem, offs + 12);
			res->sector_count_exp = ATA_INB(ch->r_mem, offs + 13);
		} else
			bzero(res, sizeof(*res));
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN &&
		    ch->numrslots == 1) {
			ccb->ataio.resid = ccb->ataio.dxfer_len -
			    ATA_INL(ch->r_mem, SIIS_P_LRAM_SLOT(slot->slot) + 4);
		}
	} else {
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN &&
		    ch->numrslots == 1) {
			ccb->csio.resid = ccb->csio.dxfer_len -
			    ATA_INL(ch->r_mem, SIIS_P_LRAM_SLOT(slot->slot) + 4);
		}
	}
	if ((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		bus_dmamap_sync(ch->dma.data_tag, slot->dma.data_map,
		    (ccb->ccb_h.flags & CAM_DIR_IN) ?
		    BUS_DMASYNC_POSTREAD : BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(ch->dma.data_tag, slot->dma.data_map);
	}
	/* Set proper result status. */
	if (et != SIIS_ERR_NONE || ch->recovery) {
		ch->eslots |= (1 << slot->slot);
		ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
	}
	/* In case of error, freeze device for proper recovery. */
	if (et != SIIS_ERR_NONE && (!ch->recoverycmd) &&
	    !(ccb->ccb_h.status & CAM_DEV_QFRZN)) {
		xpt_freeze_devq(ccb->ccb_h.path, 1);
		ccb->ccb_h.status |= CAM_DEV_QFRZN;
	}
	ccb->ccb_h.status &= ~CAM_STATUS_MASK;
	switch (et) {
	case SIIS_ERR_NONE:
		ccb->ccb_h.status |= CAM_REQ_CMP;
		if (ccb->ccb_h.func_code == XPT_SCSI_IO)
			ccb->csio.scsi_status = SCSI_STATUS_OK;
		break;
	case SIIS_ERR_INVALID:
		ch->fatalerr = 1;
		ccb->ccb_h.status |= CAM_REQ_INVALID;
		break;
	case SIIS_ERR_INNOCENT:
		ccb->ccb_h.status |= CAM_REQUEUE_REQ;
		break;
	case SIIS_ERR_TFE:
	case SIIS_ERR_NCQ:
		if (ccb->ccb_h.func_code == XPT_SCSI_IO) {
			ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
			ccb->csio.scsi_status = SCSI_STATUS_CHECK_COND;
		} else {
			ccb->ccb_h.status |= CAM_ATA_STATUS_ERROR;
		}
		break;
	case SIIS_ERR_SATA:
		ch->fatalerr = 1;
		ccb->ccb_h.status |= CAM_UNCOR_PARITY;
		break;
	case SIIS_ERR_TIMEOUT:
		ch->fatalerr = 1;
		ccb->ccb_h.status |= CAM_CMD_TIMEOUT;
		break;
	default:
		ccb->ccb_h.status |= CAM_REQ_CMP_ERR;
	}
	/* Free slot. */
	ch->oslots &= ~(1 << slot->slot);
	ch->rslots &= ~(1 << slot->slot);
	ch->aslots &= ~(1 << slot->slot);
	slot->state = SIIS_SLOT_EMPTY;
	slot->ccb = NULL;
	/* Update channel stats. */
	ch->numrslots--;
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA)) {
		ch->numtslots[ccb->ccb_h.target_id]--;
	}
	/* Cancel timeout state if request completed normally. */
	if (et != SIIS_ERR_TIMEOUT) {
		lastto = (ch->toslots == (1 << slot->slot));
		ch->toslots &= ~(1 << slot->slot);
		if (lastto)
			xpt_release_simq(ch->sim, TRUE);
	}
	/* If it was our READ LOG command - process it. */
	if (ccb->ccb_h.recovery_type == RECOVERY_READ_LOG) {
		siis_process_read_log(dev, ccb);
	/* If it was our REQUEST SENSE command - process it. */
	} else if (ccb->ccb_h.recovery_type == RECOVERY_REQUEST_SENSE) {
		siis_process_request_sense(dev, ccb);
	/* If it was NCQ or ATAPI command error, put result on hold. */
	} else if (et == SIIS_ERR_NCQ ||
	    ((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_SCSI_STATUS_ERROR &&
	     (ccb->ccb_h.flags & CAM_DIS_AUTOSENSE) == 0)) {
		ch->hold[slot->slot] = ccb;
		ch->numhslots++;
	} else
		xpt_done(ccb);
	/* If we have no other active commands, ... */
	if (ch->rslots == 0) {
		/* if there were timeouts or fatal error - reset port. */
		if (ch->toslots != 0 || ch->fatalerr) {
			siis_reset(dev);
		} else {
			/* if we have slots in error, we can reinit port. */
			if (ch->eslots != 0)
				siis_portinit(dev);
			/* if there commands on hold, we can do recovery. */
			if (!ch->recoverycmd && ch->numhslots)
				siis_issue_recovery(dev);
		}
	/* If all the reset of commands are in timeout - abort them. */
	} else if ((ch->rslots & ~ch->toslots) == 0 &&
	    et != SIIS_ERR_TIMEOUT)
		siis_rearm_timeout(dev);
	/* Unfreeze frozen command. */
	if (ch->frozen && !siis_check_collision(dev, ch->frozen)) {
		union ccb *fccb = ch->frozen;
		ch->frozen = NULL;
		siis_begin_transaction(dev, fccb);
		xpt_release_simq(ch->sim, TRUE);
	}
}