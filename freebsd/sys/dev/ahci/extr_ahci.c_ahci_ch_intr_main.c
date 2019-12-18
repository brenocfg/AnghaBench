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
struct TYPE_9__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_3__ ccb_h; } ;
typedef  int uint32_t ;
typedef  int u_int8_t ;
struct TYPE_8__ {int* rfis; } ;
struct ahci_channel {scalar_t__ numtslots; scalar_t__ numrslots; int caps; int quirks; int rslots; scalar_t__* numrslotspd; int numslots; scalar_t__* numtslotspd; int fatalerr; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  recoverycmd; TYPE_6__* slot; union ccb* frozen; scalar_t__ fbs_enabled; TYPE_2__ dma; TYPE_1__* curr; scalar_t__ pm_present; } ;
typedef  enum ahci_err_type { ____Placeholder_ahci_err_type } ahci_err_type ;
struct TYPE_12__ {TYPE_5__* ccb; } ;
struct TYPE_10__ {int target_id; } ;
struct TYPE_11__ {TYPE_4__ ccb_h; } ;
struct TYPE_7__ {scalar_t__ atapi; } ;

/* Variables and functions */
 int AHCI_CAP_SSNTF ; 
 int AHCI_ERR_INNOCENT ; 
 int AHCI_ERR_INVALID ; 
 int AHCI_ERR_NCQ ; 
 int AHCI_ERR_NONE ; 
 int AHCI_ERR_SATA ; 
 int AHCI_ERR_TFE ; 
 int /*<<< orphan*/  AHCI_P_CI ; 
 int /*<<< orphan*/  AHCI_P_CMD ; 
 int AHCI_P_CMD_CCS_MASK ; 
 int AHCI_P_CMD_CCS_SHIFT ; 
 int /*<<< orphan*/  AHCI_P_FBS ; 
 int AHCI_P_FBS_DEC ; 
 int AHCI_P_FBS_DWE ; 
 int AHCI_P_FBS_DWE_SHIFT ; 
 int AHCI_P_FBS_EN ; 
 int AHCI_P_FBS_SDE ; 
 int /*<<< orphan*/  AHCI_P_IS ; 
 int AHCI_P_IX_CPD ; 
 int AHCI_P_IX_HBD ; 
 int AHCI_P_IX_HBF ; 
 int AHCI_P_IX_IF ; 
 int AHCI_P_IX_OF ; 
 int AHCI_P_IX_PC ; 
 int AHCI_P_IX_PRC ; 
 int AHCI_P_IX_SDB ; 
 int AHCI_P_IX_TFE ; 
 int /*<<< orphan*/  AHCI_P_SACT ; 
 int /*<<< orphan*/  AHCI_P_SERR ; 
 int /*<<< orphan*/  AHCI_P_SNTF ; 
 int AHCI_Q_NOCCS ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  ahci_cpd_check_events (struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_done (struct ahci_channel*,union ccb*) ; 
 int /*<<< orphan*/  ahci_end_transaction (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ahci_notify_events (struct ahci_channel*,int) ; 
 int ahci_phy_check_events (struct ahci_channel*,int) ; 
 int ffs (int) ; 
 scalar_t__ powerof2 (int) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahci_ch_intr_main(struct ahci_channel *ch, uint32_t istatus)
{
	uint32_t cstatus, serr = 0, sntf = 0, ok, err;
	enum ahci_err_type et;
	int i, ccs, port, reset = 0;

	/* Clear interrupt statuses. */
	ATA_OUTL(ch->r_mem, AHCI_P_IS, istatus);
	/* Read command statuses. */
	if (ch->numtslots != 0)
		cstatus = ATA_INL(ch->r_mem, AHCI_P_SACT);
	else
		cstatus = 0;
	if (ch->numrslots != ch->numtslots)
		cstatus |= ATA_INL(ch->r_mem, AHCI_P_CI);
	/* Read SNTF in one of possible ways. */
	if ((istatus & AHCI_P_IX_SDB) &&
	    (ch->pm_present || ch->curr[0].atapi != 0)) {
		if (ch->caps & AHCI_CAP_SSNTF)
			sntf = ATA_INL(ch->r_mem, AHCI_P_SNTF);
		else if (ch->fbs_enabled) {
			u_int8_t *fis = ch->dma.rfis + 0x58;

			for (i = 0; i < 16; i++) {
				if (fis[1] & 0x80) {
					fis[1] &= 0x7f;
	    				sntf |= 1 << i;
	    			}
	    			fis += 256;
	    		}
		} else {
			u_int8_t *fis = ch->dma.rfis + 0x58;

			if (fis[1] & 0x80)
				sntf = (1 << (fis[1] & 0x0f));
		}
	}
	/* Process PHY events */
	if (istatus & (AHCI_P_IX_PC | AHCI_P_IX_PRC | AHCI_P_IX_OF |
	    AHCI_P_IX_IF | AHCI_P_IX_HBD | AHCI_P_IX_HBF | AHCI_P_IX_TFE)) {
		serr = ATA_INL(ch->r_mem, AHCI_P_SERR);
		if (serr) {
			ATA_OUTL(ch->r_mem, AHCI_P_SERR, serr);
			reset = ahci_phy_check_events(ch, serr);
		}
	}
	/* Process cold presence detection events */
	if ((istatus & AHCI_P_IX_CPD) && !reset)
		ahci_cpd_check_events(ch);
	/* Process command errors */
	if (istatus & (AHCI_P_IX_OF | AHCI_P_IX_IF |
	    AHCI_P_IX_HBD | AHCI_P_IX_HBF | AHCI_P_IX_TFE)) {
		if (ch->quirks & AHCI_Q_NOCCS) {
			/*
			 * ASMedia chips sometimes report failed commands as
			 * completed.  Count all running commands as failed.
			 */
			cstatus |= ch->rslots;

			/* They also report wrong CCS, so try to guess one. */
			ccs = powerof2(cstatus) ? ffs(cstatus) - 1 : -1;
		} else {
			ccs = (ATA_INL(ch->r_mem, AHCI_P_CMD) &
			    AHCI_P_CMD_CCS_MASK) >> AHCI_P_CMD_CCS_SHIFT;
		}
//device_printf(dev, "%s ERROR is %08x cs %08x ss %08x rs %08x tfd %02x serr %08x fbs %08x ccs %d\n",
//    __func__, istatus, cstatus, sstatus, ch->rslots, ATA_INL(ch->r_mem, AHCI_P_TFD),
//    serr, ATA_INL(ch->r_mem, AHCI_P_FBS), ccs);
		port = -1;
		if (ch->fbs_enabled) {
			uint32_t fbs = ATA_INL(ch->r_mem, AHCI_P_FBS);
			if (fbs & AHCI_P_FBS_SDE) {
				port = (fbs & AHCI_P_FBS_DWE)
				    >> AHCI_P_FBS_DWE_SHIFT;
			} else {
				for (i = 0; i < 16; i++) {
					if (ch->numrslotspd[i] == 0)
						continue;
					if (port == -1)
						port = i;
					else if (port != i) {
						port = -2;
						break;
					}
				}
			}
		}
		err = ch->rslots & cstatus;
	} else {
		ccs = 0;
		err = 0;
		port = -1;
	}
	/* Complete all successful commands. */
	ok = ch->rslots & ~cstatus;
	for (i = 0; i < ch->numslots; i++) {
		if ((ok >> i) & 1)
			ahci_end_transaction(&ch->slot[i], AHCI_ERR_NONE);
	}
	/* On error, complete the rest of commands with error statuses. */
	if (err) {
		if (ch->frozen) {
			union ccb *fccb = ch->frozen;
			ch->frozen = NULL;
			fccb->ccb_h.status = CAM_REQUEUE_REQ | CAM_RELEASE_SIMQ;
			if (!(fccb->ccb_h.status & CAM_DEV_QFRZN)) {
				xpt_freeze_devq(fccb->ccb_h.path, 1);
				fccb->ccb_h.status |= CAM_DEV_QFRZN;
			}
			ahci_done(ch, fccb);
		}
		for (i = 0; i < ch->numslots; i++) {
			/* XXX: reqests in loading state. */
			if (((err >> i) & 1) == 0)
				continue;
			if (port >= 0 &&
			    ch->slot[i].ccb->ccb_h.target_id != port)
				continue;
			if (istatus & AHCI_P_IX_TFE) {
			    if (port != -2) {
				/* Task File Error */
				if (ch->numtslotspd[
				    ch->slot[i].ccb->ccb_h.target_id] == 0) {
					/* Untagged operation. */
					if (i == ccs)
						et = AHCI_ERR_TFE;
					else
						et = AHCI_ERR_INNOCENT;
				} else {
					/* Tagged operation. */
					et = AHCI_ERR_NCQ;
				}
			    } else {
				et = AHCI_ERR_TFE;
				ch->fatalerr = 1;
			    }
			} else if (istatus & AHCI_P_IX_IF) {
				if (ch->numtslots == 0 && i != ccs && port != -2)
					et = AHCI_ERR_INNOCENT;
				else
					et = AHCI_ERR_SATA;
			} else
				et = AHCI_ERR_INVALID;
			ahci_end_transaction(&ch->slot[i], et);
		}
		/*
		 * We can't reinit port if there are some other
		 * commands active, use resume to complete them.
		 */
		if (ch->rslots != 0 && !ch->recoverycmd)
			ATA_OUTL(ch->r_mem, AHCI_P_FBS, AHCI_P_FBS_EN | AHCI_P_FBS_DEC);
	}
	/* Process NOTIFY events */
	if (sntf)
		ahci_notify_events(ch, sntf);
}