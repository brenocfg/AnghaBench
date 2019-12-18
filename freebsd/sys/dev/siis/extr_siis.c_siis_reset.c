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
struct TYPE_4__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int uint32_t ;
struct siis_channel {int numrslots; scalar_t__ toslots; scalar_t__ pm_level; int devices; int /*<<< orphan*/  sim; int /*<<< orphan*/  path; int /*<<< orphan*/  r_mem; scalar_t__ pm_present; TYPE_2__* user; scalar_t__ fatalerr; scalar_t__ recovery; scalar_t__ eslots; int /*<<< orphan*/  numhslots; union ccb** hold; TYPE_3__* slot; union ccb* frozen; int /*<<< orphan*/  recoverycmd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ATA_SC_DET_IDLE ; 
 int ATA_SC_IPM_DIS_PARTIAL ; 
 int ATA_SC_IPM_DIS_SLUMBER ; 
 int ATA_SC_SPD_SPEED_GEN1 ; 
 int ATA_SC_SPD_SPEED_GEN2 ; 
 int ATA_SC_SPD_SPEED_GEN3 ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SIIS_ERR_INNOCENT ; 
 int SIIS_MAX_SLOTS ; 
 int /*<<< orphan*/  SIIS_P_CTLCLR ; 
 int /*<<< orphan*/  SIIS_P_CTLSET ; 
 int SIIS_P_CTL_32BIT ; 
 int SIIS_P_CTL_PME ; 
 int SIIS_P_CTL_PORT_RESET ; 
 int /*<<< orphan*/  SIIS_P_IECLR ; 
 int /*<<< orphan*/  SIIS_P_IESET ; 
 int /*<<< orphan*/  SIIS_P_IS ; 
 int SIIS_P_IX_ENABLED ; 
 int /*<<< orphan*/  SIIS_P_SCTL ; 
 scalar_t__ SIIS_SLOT_RUNNING ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bootverbose ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  siis_devreset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_end_transaction (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_sata_connect (struct siis_channel*) ; 
 scalar_t__ siis_wait_ready (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
siis_reset(device_t dev)
{
	struct siis_channel *ch = device_get_softc(dev);
	int i, retry = 0, sata_rev;
	uint32_t val;

	xpt_freeze_simq(ch->sim, 1);
	if (bootverbose)
		device_printf(dev, "SIIS reset...\n");
	if (!ch->recoverycmd && !ch->recovery)
		xpt_freeze_simq(ch->sim, ch->numrslots);
	/* Requeue frozen command. */
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
	/* Requeue all running commands. */
	for (i = 0; i < SIIS_MAX_SLOTS; i++) {
		/* Do we have a running request on slot? */
		if (ch->slot[i].state < SIIS_SLOT_RUNNING)
			continue;
		/* XXX; Commands in loading state. */
		siis_end_transaction(&ch->slot[i], SIIS_ERR_INNOCENT);
	}
	/* Finish all held commands as-is. */
	for (i = 0; i < SIIS_MAX_SLOTS; i++) {
		if (!ch->hold[i])
			continue;
		xpt_done(ch->hold[i]);
		ch->hold[i] = NULL;
		ch->numhslots--;
	}
	if (ch->toslots != 0)
		xpt_release_simq(ch->sim, TRUE);
	ch->eslots = 0;
	ch->recovery = 0;
	ch->toslots = 0;
	ch->fatalerr = 0;
	/* Disable port interrupts */
	ATA_OUTL(ch->r_mem, SIIS_P_IECLR, 0x0000FFFF);
	/* Set speed limit. */
	sata_rev = ch->user[ch->pm_present ? 15 : 0].revision;
	if (sata_rev == 1)
		val = ATA_SC_SPD_SPEED_GEN1;
	else if (sata_rev == 2)
		val = ATA_SC_SPD_SPEED_GEN2;
	else if (sata_rev == 3)
		val = ATA_SC_SPD_SPEED_GEN3;
	else
		val = 0;
	ATA_OUTL(ch->r_mem, SIIS_P_SCTL,
	    ATA_SC_DET_IDLE | val | ((ch->pm_level > 0) ? 0 :
	    (ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER)));
retry:
	siis_devreset(dev);
	/* Reset and reconnect PHY, */
	if (!siis_sata_connect(ch)) {
		ch->devices = 0;
		/* Enable port interrupts */
		ATA_OUTL(ch->r_mem, SIIS_P_IESET, SIIS_P_IX_ENABLED);
		if (bootverbose)
			device_printf(dev,
			    "SIIS reset done: phy reset found no device\n");
		/* Tell the XPT about the event */
		xpt_async(AC_BUS_RESET, ch->path, NULL);
		xpt_release_simq(ch->sim, TRUE);
		return;
	}
	/* Wait for port ready status. */
	if (siis_wait_ready(dev, 1000)) {
		device_printf(dev, "port ready timeout\n");
		if (!retry) {
			device_printf(dev, "trying full port reset ...\n");
			/* Get port to the reset state. */
			ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_PORT_RESET);
			DELAY(10000);
			/* Get port out of reset state. */
			ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_PORT_RESET);
			ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_32BIT);
			if (ch->pm_present)
				ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_PME);
			else
				ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_PME);
			siis_wait_ready(dev, 5000);
			retry = 1;
			goto retry;
		}
	}
	ch->devices = 1;
	/* Enable port interrupts */
	ATA_OUTL(ch->r_mem, SIIS_P_IS, 0xFFFFFFFF);
	ATA_OUTL(ch->r_mem, SIIS_P_IESET, SIIS_P_IX_ENABLED);
	if (bootverbose)
		device_printf(dev, "SIIS reset done: devices=%08x\n", ch->devices);
	/* Tell the XPT about the event */
	xpt_async(AC_BUS_RESET, ch->path, NULL);
	xpt_release_simq(ch->sim, TRUE);
}