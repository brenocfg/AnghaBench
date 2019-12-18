#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mvs_channel {int resetting; scalar_t__ toslots; int devices; int /*<<< orphan*/  sim; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  path; scalar_t__ fake_busy; scalar_t__ fatalerr; scalar_t__ eslots; int /*<<< orphan*/  numhslots; int /*<<< orphan*/ ** hold; TYPE_1__* slot; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ATA_S_BUSY ; 
 int ATA_S_DRQ ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DMA_C ; 
 int /*<<< orphan*/  EDMA_CMD ; 
 int EDMA_CMD_EATARST ; 
 int /*<<< orphan*/  EDMA_IEC ; 
 int /*<<< orphan*/  EDMA_IEM ; 
 int EDMA_IE_TRANSIENT ; 
 int /*<<< orphan*/  MVS_EDMA_OFF ; 
 int /*<<< orphan*/  MVS_ERR_INNOCENT ; 
 int MVS_MAX_SLOTS ; 
 scalar_t__ MVS_SLOT_RUNNING ; 
 int /*<<< orphan*/  SATA_SE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ dumping ; 
 int hz ; 
 int /*<<< orphan*/  mvs_end_transaction (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_errata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_requeue_frozen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_reset_to ; 
 int /*<<< orphan*/  mvs_sata_phy_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_set_edma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mvs_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_reset(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	int i;

	xpt_freeze_simq(ch->sim, 1);
	if (bootverbose)
		device_printf(dev, "MVS reset...\n");
	/* Forget about previous reset. */
	if (ch->resetting) {
		ch->resetting = 0;
		callout_stop(&ch->reset_timer);
		xpt_release_simq(ch->sim, TRUE);
	}
	/* Requeue freezed command. */
	mvs_requeue_frozen(dev);
	/* Kill the engine and requeue all running commands. */
	mvs_set_edma_mode(dev, MVS_EDMA_OFF);
	ATA_OUTL(ch->r_mem, DMA_C, 0);
	for (i = 0; i < MVS_MAX_SLOTS; i++) {
		/* Do we have a running request on slot? */
		if (ch->slot[i].state < MVS_SLOT_RUNNING)
			continue;
		/* XXX; Commands in loading state. */
		mvs_end_transaction(&ch->slot[i], MVS_ERR_INNOCENT);
	}
	for (i = 0; i < MVS_MAX_SLOTS; i++) {
		if (!ch->hold[i])
			continue;
		xpt_done(ch->hold[i]);
		ch->hold[i] = NULL;
		ch->numhslots--;
	}
	if (ch->toslots != 0)
		xpt_release_simq(ch->sim, TRUE);
	ch->eslots = 0;
	ch->toslots = 0;
	ch->fatalerr = 0;
	ch->fake_busy = 0;
	/* Tell the XPT about the event */
	xpt_async(AC_BUS_RESET, ch->path, NULL);
	ATA_OUTL(ch->r_mem, EDMA_IEM, 0);
	ATA_OUTL(ch->r_mem, EDMA_CMD, EDMA_CMD_EATARST);
	DELAY(25);
	ATA_OUTL(ch->r_mem, EDMA_CMD, 0);
	mvs_errata(dev);
	/* Reset and reconnect PHY, */
	if (!mvs_sata_phy_reset(dev)) {
		if (bootverbose)
			device_printf(dev, "MVS reset: device not found\n");
		ch->devices = 0;
		ATA_OUTL(ch->r_mem, SATA_SE, 0xffffffff);
		ATA_OUTL(ch->r_mem, EDMA_IEC, 0);
		ATA_OUTL(ch->r_mem, EDMA_IEM, ~EDMA_IE_TRANSIENT);
		xpt_release_simq(ch->sim, TRUE);
		return;
	}
	if (bootverbose)
		device_printf(dev, "MVS reset: device found\n");
	/* Wait for clearing busy status. */
	if ((i = mvs_wait(dev, 0, ATA_S_BUSY | ATA_S_DRQ,
	    dumping ? 31000 : 0)) < 0) {
		if (dumping) {
			device_printf(dev,
			    "MVS reset: device not ready after 31000ms\n");
		} else
			ch->resetting = 310;
	} else if (bootverbose)
		device_printf(dev, "MVS reset: device ready after %dms\n", i);
	ch->devices = 1;
	ATA_OUTL(ch->r_mem, SATA_SE, 0xffffffff);
	ATA_OUTL(ch->r_mem, EDMA_IEC, 0);
	ATA_OUTL(ch->r_mem, EDMA_IEM, ~EDMA_IE_TRANSIENT);
	if (ch->resetting)
		callout_reset(&ch->reset_timer, hz / 10, mvs_reset_to, dev);
	else
		xpt_release_simq(ch->sim, TRUE);
}