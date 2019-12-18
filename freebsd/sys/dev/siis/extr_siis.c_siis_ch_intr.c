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
struct TYPE_5__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int uint32_t ;
struct siis_channel {int rslots; int recovery; int* numtslots; TYPE_4__* slot; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  recoverycmd; union ccb* frozen; int /*<<< orphan*/  numrslots; int /*<<< orphan*/  sim; int /*<<< orphan*/  mtx; } ;
typedef  enum siis_err_type { ____Placeholder_siis_err_type } siis_err_type ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {TYPE_3__* ccb; } ;
struct TYPE_6__ {int target_id; } ;
struct TYPE_7__ {TYPE_2__ ccb_h; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SIIS_ERR_INNOCENT ; 
 int SIIS_ERR_INVALID ; 
 int SIIS_ERR_NCQ ; 
 int SIIS_ERR_NONE ; 
 int SIIS_ERR_SATA ; 
 int SIIS_ERR_TFE ; 
 int SIIS_MAX_SLOTS ; 
 int /*<<< orphan*/  SIIS_P_CMDERR ; 
 int SIIS_P_CMDERR_DATAFIS ; 
 int SIIS_P_CMDERR_DEV ; 
 int SIIS_P_CMDERR_INCSTATE ; 
 int SIIS_P_CMDERR_PPE ; 
 int SIIS_P_CMDERR_SDB ; 
 int SIIS_P_CMDERR_SENDFIS ; 
 int SIIS_P_CMDERR_SERVICE ; 
 int /*<<< orphan*/  SIIS_P_CTLSET ; 
 int SIIS_P_CTL_RESUME ; 
 int /*<<< orphan*/  SIIS_P_CTX ; 
 int SIIS_P_CTX_PMP ; 
 int SIIS_P_CTX_PMP_SHIFT ; 
 int SIIS_P_CTX_SLOT ; 
 int SIIS_P_CTX_SLOT_SHIFT ; 
 int /*<<< orphan*/  SIIS_P_IS ; 
 int SIIS_P_IX_COMMCOMP ; 
 int SIIS_P_IX_COMMERR ; 
 int SIIS_P_IX_PHYRDYCHG ; 
 int SIIS_P_IX_SDBN ; 
 int /*<<< orphan*/  SIIS_P_SS ; 
 int SIIS_P_SS_ATTN ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_end_transaction (TYPE_4__*,int) ; 
 int /*<<< orphan*/  siis_notify_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_phy_check_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
siis_ch_intr(void *data)
{
	device_t dev = (device_t)data;
	struct siis_channel *ch = device_get_softc(dev);
	uint32_t istatus, sstatus, ctx, estatus, ok, err = 0;
	enum siis_err_type et;
	int i, ccs, port, tslots;

	mtx_assert(&ch->mtx, MA_OWNED);
	/* Read command statuses. */
	sstatus = ATA_INL(ch->r_mem, SIIS_P_SS);
	ok = ch->rslots & ~sstatus;
	/* Complete all successful commands. */
	for (i = 0; i < SIIS_MAX_SLOTS; i++) {
		if ((ok >> i) & 1)
			siis_end_transaction(&ch->slot[i], SIIS_ERR_NONE);
	}
	/* Do we have any other events? */
	if ((sstatus & SIIS_P_SS_ATTN) == 0)
		return;
	/* Read and clear interrupt statuses. */
	istatus = ATA_INL(ch->r_mem, SIIS_P_IS) &
	    (0xFFFF & ~SIIS_P_IX_COMMCOMP);
	ATA_OUTL(ch->r_mem, SIIS_P_IS, istatus);
	/* Process PHY events */
	if (istatus & SIIS_P_IX_PHYRDYCHG)
		siis_phy_check_events(dev);
	/* Process NOTIFY events */
	if (istatus & SIIS_P_IX_SDBN)
		siis_notify_events(dev);
	/* Process command errors */
	if (istatus & SIIS_P_IX_COMMERR) {
		estatus = ATA_INL(ch->r_mem, SIIS_P_CMDERR);
		ctx = ATA_INL(ch->r_mem, SIIS_P_CTX);
		ccs = (ctx & SIIS_P_CTX_SLOT) >> SIIS_P_CTX_SLOT_SHIFT;
		port = (ctx & SIIS_P_CTX_PMP) >> SIIS_P_CTX_PMP_SHIFT;
		err = ch->rslots & sstatus;
//device_printf(dev, "%s ERROR ss %08x is %08x rs %08x es %d act %d port %d serr %08x\n",
//    __func__, sstatus, istatus, ch->rslots, estatus, ccs, port,
//    ATA_INL(ch->r_mem, SIIS_P_SERR));

		if (!ch->recoverycmd && !ch->recovery) {
			xpt_freeze_simq(ch->sim, ch->numrslots);
			ch->recovery = 1;
		}
		if (ch->frozen) {
			union ccb *fccb = ch->frozen;
			ch->frozen = NULL;
			fccb->ccb_h.status &= ~CAM_STATUS_MASK;
			fccb->ccb_h.status |= CAM_REQUEUE_REQ | CAM_RELEASE_SIMQ;
			if (!(fccb->ccb_h.status & CAM_DEV_QFRZN)) {
				xpt_freeze_devq(fccb->ccb_h.path, 1);
				fccb->ccb_h.status |= CAM_DEV_QFRZN;
			}
			xpt_done(fccb);
		}
		if (estatus == SIIS_P_CMDERR_DEV ||
		    estatus == SIIS_P_CMDERR_SDB ||
		    estatus == SIIS_P_CMDERR_DATAFIS) {
			tslots = ch->numtslots[port];
			for (i = 0; i < SIIS_MAX_SLOTS; i++) {
				/* XXX: requests in loading state. */
				if (((ch->rslots >> i) & 1) == 0)
					continue;
				if (ch->slot[i].ccb->ccb_h.target_id != port)
					continue;
				if (tslots == 0) {
					/* Untagged operation. */
					if (i == ccs)
						et = SIIS_ERR_TFE;
					else
						et = SIIS_ERR_INNOCENT;
				} else {
					/* Tagged operation. */
					et = SIIS_ERR_NCQ;
				}
				siis_end_transaction(&ch->slot[i], et);
			}
			/*
			 * We can't reinit port if there are some other
			 * commands active, use resume to complete them.
			 */
			if (ch->rslots != 0 && !ch->recoverycmd)
				ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_RESUME);
		} else {
			if (estatus == SIIS_P_CMDERR_SENDFIS ||
			    estatus == SIIS_P_CMDERR_INCSTATE ||
			    estatus == SIIS_P_CMDERR_PPE ||
			    estatus == SIIS_P_CMDERR_SERVICE) {
				et = SIIS_ERR_SATA;
			} else
				et = SIIS_ERR_INVALID;
			for (i = 0; i < SIIS_MAX_SLOTS; i++) {
				/* XXX: requests in loading state. */
				if (((ch->rslots >> i) & 1) == 0)
					continue;
				siis_end_transaction(&ch->slot[i], et);
			}
		}
	}
}