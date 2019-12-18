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
typedef  int uint32_t ;
struct fsl_sata_channel {scalar_t__ toslots; int devices; int /*<<< orphan*/  sim; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  dev; int /*<<< orphan*/  path; scalar_t__ fatalerr; scalar_t__ eslots; int /*<<< orphan*/  numhslots; union ccb** hold; TYPE_2__* slot; union ccb* frozen; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FSL_SATA_ERR_INNOCENT ; 
 int FSL_SATA_MAX_SLOTS ; 
 int /*<<< orphan*/  FSL_SATA_P_HCTRL ; 
 int FSL_SATA_P_HCTRL_CC ; 
 int FSL_SATA_P_HCTRL_DE ; 
 int FSL_SATA_P_HCTRL_FATAL ; 
 int FSL_SATA_P_HCTRL_PHYRDY ; 
 int FSL_SATA_P_HCTRL_SIG ; 
 int FSL_SATA_P_HCTRL_SNTFY ; 
 int /*<<< orphan*/  FSL_SATA_P_HSTS ; 
 scalar_t__ FSL_SATA_SLOT_RUNNING ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsl_sata_done (struct fsl_sata_channel*,union ccb*) ; 
 int /*<<< orphan*/  fsl_sata_end_transaction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_start (struct fsl_sata_channel*) ; 
 int /*<<< orphan*/  fsl_sata_stop (struct fsl_sata_channel*) ; 
 scalar_t__ fsl_sata_wait_register (struct fsl_sata_channel*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsl_sata_reset(struct fsl_sata_channel *ch)
{
	uint32_t ctrl;
	int i;

	xpt_freeze_simq(ch->sim, 1);
	if (bootverbose)
		device_printf(ch->dev, "FSL SATA reset...\n");

	/* Requeue freezed command. */
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
	/* Kill the engine and requeue all running commands. */
	fsl_sata_stop(ch);
	DELAY(1000);	/* sleep for 1ms */
	for (i = 0; i < FSL_SATA_MAX_SLOTS; i++) {
		/* Do we have a running request on slot? */
		if (ch->slot[i].state < FSL_SATA_SLOT_RUNNING)
			continue;
		/* XXX; Commands in loading state. */
		fsl_sata_end_transaction(&ch->slot[i], FSL_SATA_ERR_INNOCENT);
	}
	for (i = 0; i < FSL_SATA_MAX_SLOTS; i++) {
		if (!ch->hold[i])
			continue;
		fsl_sata_done(ch, ch->hold[i]);
		ch->hold[i] = NULL;
		ch->numhslots--;
	}
	if (ch->toslots != 0)
		xpt_release_simq(ch->sim, TRUE);
	ch->eslots = 0;
	ch->toslots = 0;
	ch->fatalerr = 0;
	/* Tell the XPT about the event */
	xpt_async(AC_BUS_RESET, ch->path, NULL);
	/* Disable port interrupts */
	ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL,
	    ATA_INL(ch->r_mem, FSL_SATA_P_HCTRL) & ~0x3f);
	/* Reset and reconnect PHY, */
	fsl_sata_start(ch);
	if (fsl_sata_wait_register(ch, FSL_SATA_P_HSTS, 0x08, 0x08, 500)) {
		if (bootverbose)
			device_printf(ch->dev,
			    "FSL SATA reset: device not found\n");
		ch->devices = 0;
		/* Enable wanted port interrupts */
		ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL,
		    ATA_INL(ch->r_mem, FSL_SATA_P_HCTRL) | FSL_SATA_P_HCTRL_PHYRDY);
		xpt_release_simq(ch->sim, TRUE);
		return;
	}
	if (bootverbose)
		device_printf(ch->dev, "FSL SATA reset: device found\n");
	ch->devices = 1;
	/* Enable wanted port interrupts */
	ctrl = ATA_INL(ch->r_mem, FSL_SATA_P_HCTRL) & ~0x3f;
	ATA_OUTL(ch->r_mem, FSL_SATA_P_HCTRL,
	    ctrl | FSL_SATA_P_HCTRL_FATAL | FSL_SATA_P_HCTRL_PHYRDY |
	    FSL_SATA_P_HCTRL_SIG | FSL_SATA_P_HCTRL_SNTFY |
	    FSL_SATA_P_HCTRL_DE | FSL_SATA_P_HCTRL_CC);
	xpt_release_simq(ch->sim, TRUE);
}