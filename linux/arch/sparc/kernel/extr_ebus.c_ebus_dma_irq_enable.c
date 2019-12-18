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
typedef  int /*<<< orphan*/  u32 ;
struct ebus_dma_info {int flags; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; scalar_t__ regs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EBDMA_CSR ; 
 int /*<<< orphan*/  EBDMA_CSR_INT_EN ; 
 int EBUSY ; 
 int EBUS_DMA_FLAG_USE_EBDMA_HANDLER ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ebus_dma_irq ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ebus_dma_info*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ebus_dma_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int ebus_dma_irq_enable(struct ebus_dma_info *p, int on)
{
	unsigned long flags;
	u32 csr;

	if (on) {
		if (p->flags & EBUS_DMA_FLAG_USE_EBDMA_HANDLER) {
			if (request_irq(p->irq, ebus_dma_irq, IRQF_SHARED, p->name, p))
				return -EBUSY;
		}

		spin_lock_irqsave(&p->lock, flags);
		csr = readl(p->regs + EBDMA_CSR);
		csr |= EBDMA_CSR_INT_EN;
		writel(csr, p->regs + EBDMA_CSR);
		spin_unlock_irqrestore(&p->lock, flags);
	} else {
		spin_lock_irqsave(&p->lock, flags);
		csr = readl(p->regs + EBDMA_CSR);
		csr &= ~EBDMA_CSR_INT_EN;
		writel(csr, p->regs + EBDMA_CSR);
		spin_unlock_irqrestore(&p->lock, flags);

		if (p->flags & EBUS_DMA_FLAG_USE_EBDMA_HANDLER) {
			free_irq(p->irq, p);
		}
	}

	return 0;
}