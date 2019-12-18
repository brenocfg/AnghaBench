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
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_link {scalar_t__ sata_spd; int /*<<< orphan*/  hw_sata_spd_limit; int /*<<< orphan*/  sata_spd_limit; struct ata_port* ap; } ;
struct ata_device {void* udma_mask; void* mwdma_mask; void* pio_mask; scalar_t__ horkage; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ATA_DEVICE_CLEAR_BEGIN ; 
 int ATA_DEVICE_CLEAR_END ; 
 int /*<<< orphan*/  ATA_DFLAG_INIT_MASK ; 
 void* UINT_MAX ; 
 struct ata_link* ata_dev_phys_link (struct ata_device*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_dev_init(struct ata_device *dev)
{
	struct ata_link *link = ata_dev_phys_link(dev);
	struct ata_port *ap = link->ap;
	unsigned long flags;

	/* SATA spd limit is bound to the attached device, reset together */
	link->sata_spd_limit = link->hw_sata_spd_limit;
	link->sata_spd = 0;

	/* High bits of dev->flags are used to record warm plug
	 * requests which occur asynchronously.  Synchronize using
	 * host lock.
	 */
	spin_lock_irqsave(ap->lock, flags);
	dev->flags &= ~ATA_DFLAG_INIT_MASK;
	dev->horkage = 0;
	spin_unlock_irqrestore(ap->lock, flags);

	memset((void *)dev + ATA_DEVICE_CLEAR_BEGIN, 0,
	       ATA_DEVICE_CLEAR_END - ATA_DEVICE_CLEAR_BEGIN);
	dev->pio_mask = UINT_MAX;
	dev->mwdma_mask = UINT_MAX;
	dev->udma_mask = UINT_MAX;
}