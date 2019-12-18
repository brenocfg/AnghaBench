#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mvs_slot {scalar_t__ state; int slot; int /*<<< orphan*/  dev; } ;
struct mvs_channel {int rslots; int toslots; int /*<<< orphan*/  sim; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ALTSTAT ; 
 int /*<<< orphan*/  ATA_INB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_C ; 
 int /*<<< orphan*/  DMA_S ; 
 int /*<<< orphan*/  EDMA_IEC ; 
 int /*<<< orphan*/  EDMA_S ; 
 scalar_t__ MVS_SLOT_RUNNING ; 
 int /*<<< orphan*/  SATA_SE ; 
 int /*<<< orphan*/  SATA_SS ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mvs_process_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_requeue_frozen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mvs_timeout(struct mvs_slot *slot)
{
	device_t dev = slot->dev;
	struct mvs_channel *ch = device_get_softc(dev);

	/* Check for stale timeout. */
	if (slot->state < MVS_SLOT_RUNNING)
		return;
	device_printf(dev, "Timeout on slot %d\n", slot->slot);
	device_printf(dev, "iec %08x sstat %08x serr %08x edma_s %08x "
	    "dma_c %08x dma_s %08x rs %08x status %02x\n",
	    ATA_INL(ch->r_mem, EDMA_IEC),
	    ATA_INL(ch->r_mem, SATA_SS), ATA_INL(ch->r_mem, SATA_SE),
	    ATA_INL(ch->r_mem, EDMA_S), ATA_INL(ch->r_mem, DMA_C),
	    ATA_INL(ch->r_mem, DMA_S), ch->rslots,
	    ATA_INB(ch->r_mem, ATA_ALTSTAT));
	/* Handle frozen command. */
	mvs_requeue_frozen(dev);
	/* We wait for other commands timeout and pray. */
	if (ch->toslots == 0)
		xpt_freeze_simq(ch->sim, 1);
	ch->toslots |= (1 << slot->slot);
	if ((ch->rslots & ~ch->toslots) == 0)
		mvs_process_timeout(dev);
	else
		device_printf(dev, " ... waiting for slots %08x\n",
		    ch->rslots & ~ch->toslots);
}