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
typedef  int u32 ;
struct ebus_dma_info {int flags; int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ EBDMA_CSR ; 
 int EBDMA_CSR_BURST_SZ_16 ; 
 int EBDMA_CSR_EN_CNT ; 
 int EBDMA_CSR_EN_NEXT ; 
 int EBDMA_CSR_INT_EN ; 
 int EBDMA_CSR_TCI_DIS ; 
 int EBDMA_CSR_WRITE ; 
 int EBUS_DMA_FLAG_TCI_DISABLE ; 
 int /*<<< orphan*/  __ebus_dma_reset (struct ebus_dma_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ebus_dma_prepare(struct ebus_dma_info *p, int write)
{
	unsigned long flags;
	u32 csr;

	spin_lock_irqsave(&p->lock, flags);
	__ebus_dma_reset(p, 0);

	csr = (EBDMA_CSR_INT_EN |
	       EBDMA_CSR_EN_CNT |
	       EBDMA_CSR_BURST_SZ_16 |
	       EBDMA_CSR_EN_NEXT);

	if (write)
		csr |= EBDMA_CSR_WRITE;
	if (p->flags & EBUS_DMA_FLAG_TCI_DISABLE)
		csr |= EBDMA_CSR_TCI_DIS;

	writel(csr, p->regs + EBDMA_CSR);

	spin_unlock_irqrestore(&p->lock, flags);
}