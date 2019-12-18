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
struct ltq_dma_channel {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHAN_ON ; 
 int /*<<< orphan*/  LTQ_DMA_CCTRL ; 
 int /*<<< orphan*/  LTQ_DMA_CS ; 
 int /*<<< orphan*/  ltq_dma_lock ; 
 int /*<<< orphan*/  ltq_dma_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_w32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
ltq_dma_open(struct ltq_dma_channel *ch)
{
	unsigned long flag;

	spin_lock_irqsave(&ltq_dma_lock, flag);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32_mask(0, DMA_CHAN_ON, LTQ_DMA_CCTRL);
	spin_unlock_irqrestore(&ltq_dma_lock, flag);
}