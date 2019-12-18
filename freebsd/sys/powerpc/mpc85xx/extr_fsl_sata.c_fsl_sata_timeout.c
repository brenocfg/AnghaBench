#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_3__ ccb_h; } ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  timeout_t ;
struct fsl_sata_slot {scalar_t__ state; int slot; TYPE_2__* ccb; int /*<<< orphan*/  timeout; struct fsl_sata_channel* ch; } ;
struct fsl_sata_channel {int toslots; int rslots; int /*<<< orphan*/  sim; union ccb* frozen; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int timeout; int target_id; } ;
struct TYPE_5__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  FSL_SATA_P_CAR ; 
 scalar_t__ FSL_SATA_SLOT_EXECUTING ; 
 scalar_t__ FSL_SATA_SLOT_RUNNING ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fsl_sata_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  fsl_sata_done (struct fsl_sata_channel*,union ccb*) ; 
 int /*<<< orphan*/  fsl_sata_process_timeout (struct fsl_sata_channel*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fsl_sata_timeout(struct fsl_sata_slot *slot)
{
	struct fsl_sata_channel *ch = slot->ch;
	device_t dev = ch->dev;
	uint32_t sstatus;

	/* Check for stale timeout. */
	if (slot->state < FSL_SATA_SLOT_RUNNING)
		return;

	/* Check if slot was not being executed last time we checked. */
	if (slot->state < FSL_SATA_SLOT_EXECUTING) {
		/* Check if slot started executing. */
		sstatus = ATA_INL(ch->r_mem, FSL_SATA_P_CAR);
		if ((sstatus & (1 << slot->slot)) != 0)
			slot->state = FSL_SATA_SLOT_EXECUTING;

		callout_reset_sbt(&slot->timeout,
	    	    SBT_1MS * slot->ccb->ccb_h.timeout / 2, 0,
		    (timeout_t*)fsl_sata_timeout, slot, 0);
		return;
	}

	device_printf(dev, "Timeout on slot %d port %d\n",
	    slot->slot, slot->ccb->ccb_h.target_id & 0x0f);

	/* Handle frozen command. */
	if (ch->frozen) {
		union ccb *fccb = ch->frozen;
		ch->frozen = NULL;
		fccb->ccb_h.status = CAM_REQUEUE_REQ | CAM_RELEASE_SIMQ;
		if (!(fccb->ccb_h.status & CAM_DEV_QFRZN)) {
			xpt_freeze_devq(fccb->ccb_h.path, 1);
			fccb->ccb_h.status |= CAM_DEV_QFRZN;
		}
		fsl_sata_done(ch, fccb);
	}
	if (ch->toslots == 0)
		xpt_freeze_simq(ch->sim, 1);
	ch->toslots |= (1 << slot->slot);
	if ((ch->rslots & ~ch->toslots) == 0)
		fsl_sata_process_timeout(ch);
	else
		device_printf(dev, " ... waiting for slots %08x\n",
		    ch->rslots & ~ch->toslots);
}