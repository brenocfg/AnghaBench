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
typedef  int u32 ;
struct TYPE_4__ {int flags; } ;
struct ata_queued_cmd {TYPE_2__ tf; } ;
struct ata_host {struct arasan_cf_dev* private_data; } ;
struct arasan_cf_dev {int /*<<< orphan*/  cf_completion; struct ata_queued_cmd* qc; TYPE_1__* host; scalar_t__ vbase; int /*<<< orphan*/  dma_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_ERR ; 
 int ATA_TFLAG_WRITE ; 
 int BUF_AVAIL_IRQ ; 
 int CARD_DETECT_IRQ ; 
 int GIRQ_CF ; 
 scalar_t__ GIRQ_STS ; 
 int IGNORED_IRQS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ IRQ_STS ; 
 int PIO_XFER_ERR_IRQ ; 
 scalar_t__ XFER_CTR ; 
 int XFER_DONE_IRQ ; 
 int XFER_START ; 
 int /*<<< orphan*/  cf_card_detect (struct arasan_cf_dev*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t arasan_cf_interrupt(int irq, void *dev)
{
	struct arasan_cf_dev *acdev = ((struct ata_host *)dev)->private_data;
	unsigned long flags;
	u32 irqsts;

	irqsts = readl(acdev->vbase + GIRQ_STS);
	if (!(irqsts & GIRQ_CF))
		return IRQ_NONE;

	spin_lock_irqsave(&acdev->host->lock, flags);
	irqsts = readl(acdev->vbase + IRQ_STS);
	writel(irqsts, acdev->vbase + IRQ_STS);		/* clear irqs */
	writel(GIRQ_CF, acdev->vbase + GIRQ_STS);	/* clear girqs */

	/* handle only relevant interrupts */
	irqsts &= ~IGNORED_IRQS;

	if (irqsts & CARD_DETECT_IRQ) {
		cf_card_detect(acdev, 1);
		spin_unlock_irqrestore(&acdev->host->lock, flags);
		return IRQ_HANDLED;
	}

	if (irqsts & PIO_XFER_ERR_IRQ) {
		acdev->dma_status = ATA_DMA_ERR;
		writel(readl(acdev->vbase + XFER_CTR) & ~XFER_START,
				acdev->vbase + XFER_CTR);
		spin_unlock_irqrestore(&acdev->host->lock, flags);
		complete(&acdev->cf_completion);
		dev_err(acdev->host->dev, "pio xfer err irq\n");
		return IRQ_HANDLED;
	}

	spin_unlock_irqrestore(&acdev->host->lock, flags);

	if (irqsts & BUF_AVAIL_IRQ) {
		complete(&acdev->cf_completion);
		return IRQ_HANDLED;
	}

	if (irqsts & XFER_DONE_IRQ) {
		struct ata_queued_cmd *qc = acdev->qc;

		/* Send Complete only for write */
		if (qc->tf.flags & ATA_TFLAG_WRITE)
			complete(&acdev->cf_completion);
	}

	return IRQ_HANDLED;
}