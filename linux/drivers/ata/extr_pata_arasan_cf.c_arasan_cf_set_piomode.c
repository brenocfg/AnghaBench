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
typedef  int u8 ;
typedef  int u32 ;
struct ata_port {int /*<<< orphan*/  dev; TYPE_1__* host; } ;
struct ata_device {int pio_mode; } ;
struct arasan_cf_dev {TYPE_2__* host; scalar_t__ vbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct arasan_cf_dev* private_data; } ;

/* Variables and functions */
 int BUF_AVAIL_IRQ ; 
 int DRQ_BLOCK_SIZE_MASK ; 
 int MULTI_WORD_DMA_ENB ; 
 scalar_t__ OP_MODE ; 
 int PIO_XFER_ERR_IRQ ; 
 scalar_t__ TM_CFG ; 
 int TRUEIDE_PIO_TIMING_MASK ; 
 int TRUEIDE_PIO_TIMING_SHIFT ; 
 int ULTRA_DMA_ENB ; 
 int XFER_DONE_IRQ ; 
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  cf_interrupt_enable (struct arasan_cf_dev*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void arasan_cf_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct arasan_cf_dev *acdev = ap->host->private_data;
	u8 pio = adev->pio_mode - XFER_PIO_0;
	unsigned long flags;
	u32 val;

	/* Arasan ctrl supports Mode0 -> Mode6 */
	if (pio > 6) {
		dev_err(ap->dev, "Unknown PIO mode\n");
		return;
	}

	spin_lock_irqsave(&acdev->host->lock, flags);
	val = readl(acdev->vbase + OP_MODE) &
		~(ULTRA_DMA_ENB | MULTI_WORD_DMA_ENB | DRQ_BLOCK_SIZE_MASK);
	writel(val, acdev->vbase + OP_MODE);
	val = readl(acdev->vbase + TM_CFG) & ~TRUEIDE_PIO_TIMING_MASK;
	val |= pio << TRUEIDE_PIO_TIMING_SHIFT;
	writel(val, acdev->vbase + TM_CFG);

	cf_interrupt_enable(acdev, BUF_AVAIL_IRQ | XFER_DONE_IRQ, 0);
	cf_interrupt_enable(acdev, PIO_XFER_ERR_IRQ, 1);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
}