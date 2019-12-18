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
struct TYPE_3__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct ahci_controller {scalar_t__ ccc; } ;
struct ahci_channel {int resetting; int numslots; scalar_t__ toslots; int devices; scalar_t__ pm_level; int /*<<< orphan*/  sim; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  dev; int /*<<< orphan*/  path; scalar_t__ fatalerr; scalar_t__ wrongccs; scalar_t__ eslots; int /*<<< orphan*/  numhslots; union ccb** hold; TYPE_2__* slot; union ccb* frozen; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int /*<<< orphan*/  AHCI_ERR_INNOCENT ; 
 int /*<<< orphan*/  AHCI_P_IE ; 
 int AHCI_P_IX_CPD ; 
 int AHCI_P_IX_DHR ; 
 int AHCI_P_IX_DP ; 
 int AHCI_P_IX_DS ; 
 int AHCI_P_IX_HBD ; 
 int AHCI_P_IX_HBF ; 
 int AHCI_P_IX_IF ; 
 int AHCI_P_IX_MP ; 
 int AHCI_P_IX_OF ; 
 int AHCI_P_IX_PC ; 
 int AHCI_P_IX_PRC ; 
 int AHCI_P_IX_PS ; 
 int AHCI_P_IX_SDB ; 
 int AHCI_P_IX_TFE ; 
 int AHCI_P_IX_UF ; 
 scalar_t__ AHCI_SLOT_RUNNING ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahci_clo (struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_done (struct ahci_channel*,union ccb*) ; 
 int /*<<< orphan*/  ahci_end_transaction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_reset_to ; 
 int /*<<< orphan*/  ahci_sata_phy_reset (struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_start (struct ahci_channel*,int) ; 
 int /*<<< orphan*/  ahci_stop (struct ahci_channel*) ; 
 scalar_t__ ahci_wait_ready (struct ahci_channel*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ahci_channel*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dumping ; 
 int hz ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_reset(struct ahci_channel *ch)
{
	struct ahci_controller *ctlr = device_get_softc(device_get_parent(ch->dev));
	int i;

	xpt_freeze_simq(ch->sim, 1);
	if (bootverbose)
		device_printf(ch->dev, "AHCI reset...\n");
	/* Forget about previous reset. */
	if (ch->resetting) {
		ch->resetting = 0;
		callout_stop(&ch->reset_timer);
		xpt_release_simq(ch->sim, TRUE);
	}
	/* Requeue freezed command. */
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
	/* Kill the engine and requeue all running commands. */
	ahci_stop(ch);
	for (i = 0; i < ch->numslots; i++) {
		/* Do we have a running request on slot? */
		if (ch->slot[i].state < AHCI_SLOT_RUNNING)
			continue;
		/* XXX; Commands in loading state. */
		ahci_end_transaction(&ch->slot[i], AHCI_ERR_INNOCENT);
	}
	for (i = 0; i < ch->numslots; i++) {
		if (!ch->hold[i])
			continue;
		ahci_done(ch, ch->hold[i]);
		ch->hold[i] = NULL;
		ch->numhslots--;
	}
	if (ch->toslots != 0)
		xpt_release_simq(ch->sim, TRUE);
	ch->eslots = 0;
	ch->toslots = 0;
	ch->wrongccs = 0;
	ch->fatalerr = 0;
	/* Tell the XPT about the event */
	xpt_async(AC_BUS_RESET, ch->path, NULL);
	/* Disable port interrupts */
	ATA_OUTL(ch->r_mem, AHCI_P_IE, 0);
	/* Reset and reconnect PHY, */
	if (!ahci_sata_phy_reset(ch)) {
		if (bootverbose)
			device_printf(ch->dev,
			    "AHCI reset: device not found\n");
		ch->devices = 0;
		/* Enable wanted port interrupts */
		ATA_OUTL(ch->r_mem, AHCI_P_IE,
		    (((ch->pm_level != 0) ? AHCI_P_IX_CPD | AHCI_P_IX_MP : 0) |
		     AHCI_P_IX_PRC | AHCI_P_IX_PC));
		xpt_release_simq(ch->sim, TRUE);
		return;
	}
	if (bootverbose)
		device_printf(ch->dev, "AHCI reset: device found\n");
	/* Wait for clearing busy status. */
	if (ahci_wait_ready(ch, dumping ? 31000 : 0, 0)) {
		if (dumping)
			ahci_clo(ch);
		else
			ch->resetting = 310;
	}
	ch->devices = 1;
	/* Enable wanted port interrupts */
	ATA_OUTL(ch->r_mem, AHCI_P_IE,
	     (((ch->pm_level != 0) ? AHCI_P_IX_CPD | AHCI_P_IX_MP : 0) |
	      AHCI_P_IX_TFE | AHCI_P_IX_HBF |
	      AHCI_P_IX_HBD | AHCI_P_IX_IF | AHCI_P_IX_OF |
	      ((ch->pm_level == 0) ? AHCI_P_IX_PRC : 0) | AHCI_P_IX_PC |
	      AHCI_P_IX_DP | AHCI_P_IX_UF | (ctlr->ccc ? 0 : AHCI_P_IX_SDB) |
	      AHCI_P_IX_DS | AHCI_P_IX_PS | (ctlr->ccc ? 0 : AHCI_P_IX_DHR)));
	if (ch->resetting)
		callout_reset(&ch->reset_timer, hz / 10, ahci_reset_to, ch);
	else {
		ahci_start(ch, 1);
		xpt_release_simq(ch->sim, TRUE);
	}
}