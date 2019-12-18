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
typedef  size_t u8 ;
struct sata_dwc_device_port {int dma_interrupt_count; scalar_t__* dma_pending; } ;
struct sata_dwc_device {scalar_t__ host; } ;
struct TYPE_2__ {size_t active_tag; } ;
struct ata_port {int /*<<< orphan*/  dev; TYPE_1__ link; } ;
struct ata_host {int /*<<< orphan*/  lock; struct ata_port** ports; } ;

/* Variables and functions */
 struct sata_dwc_device_port* HSDEVP_FROM_AP (struct ata_port*) ; 
 scalar_t__ SATA_DWC_DMA_PENDING_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  sata_dwc_clear_dmacr (struct sata_dwc_device_port*,size_t) ; 
 int /*<<< orphan*/  sata_dwc_dma_xfer_complete (struct ata_port*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dma_dwc_xfer_done(void *hsdev_instance)
{
	unsigned long flags;
	struct sata_dwc_device *hsdev = hsdev_instance;
	struct ata_host *host = (struct ata_host *)hsdev->host;
	struct ata_port *ap;
	struct sata_dwc_device_port *hsdevp;
	u8 tag = 0;
	unsigned int port = 0;

	spin_lock_irqsave(&host->lock, flags);
	ap = host->ports[port];
	hsdevp = HSDEVP_FROM_AP(ap);
	tag = ap->link.active_tag;

	/*
	 * Each DMA command produces 2 interrupts.  Only
	 * complete the command after both interrupts have been
	 * seen. (See sata_dwc_isr())
	 */
	hsdevp->dma_interrupt_count++;
	sata_dwc_clear_dmacr(hsdevp, tag);

	if (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_NONE) {
		dev_err(ap->dev, "DMA not pending tag=0x%02x pending=%d\n",
			tag, hsdevp->dma_pending[tag]);
	}

	if ((hsdevp->dma_interrupt_count % 2) == 0)
		sata_dwc_dma_xfer_complete(ap, 1);

	spin_unlock_irqrestore(&host->lock, flags);
}