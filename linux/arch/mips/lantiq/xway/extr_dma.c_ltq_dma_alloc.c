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
struct ltq_dma_channel {int phys; int nr; int /*<<< orphan*/  dev; int /*<<< orphan*/  desc_base; scalar_t__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHAN_ON ; 
 int DMA_CHAN_RST ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LTQ_DESC_NUM ; 
 int LTQ_DESC_SIZE ; 
 int /*<<< orphan*/  LTQ_DMA_CCTRL ; 
 int /*<<< orphan*/  LTQ_DMA_CDBA ; 
 int /*<<< orphan*/  LTQ_DMA_CDLEN ; 
 int /*<<< orphan*/  LTQ_DMA_CS ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_lock ; 
 int ltq_dma_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_w32_mask (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
ltq_dma_alloc(struct ltq_dma_channel *ch)
{
	unsigned long flags;

	ch->desc = 0;
	ch->desc_base = dma_alloc_coherent(ch->dev,
					   LTQ_DESC_NUM * LTQ_DESC_SIZE,
					   &ch->phys, GFP_ATOMIC);

	spin_lock_irqsave(&ltq_dma_lock, flags);
	ltq_dma_w32(ch->nr, LTQ_DMA_CS);
	ltq_dma_w32(ch->phys, LTQ_DMA_CDBA);
	ltq_dma_w32(LTQ_DESC_NUM, LTQ_DMA_CDLEN);
	ltq_dma_w32_mask(DMA_CHAN_ON, 0, LTQ_DMA_CCTRL);
	wmb();
	ltq_dma_w32_mask(0, DMA_CHAN_RST, LTQ_DMA_CCTRL);
	while (ltq_dma_r32(LTQ_DMA_CCTRL) & DMA_CHAN_RST)
		;
	spin_unlock_irqrestore(&ltq_dma_lock, flags);
}