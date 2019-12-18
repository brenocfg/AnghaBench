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
struct xgene_dma_ring {size_t head; size_t slots; int /*<<< orphan*/  cmd; struct xgene_dma_desc_hw* desc_hw; } ;
struct xgene_dma_desc_sw {int flags; int /*<<< orphan*/  desc2; int /*<<< orphan*/  desc1; } ;
struct xgene_dma_desc_hw {int dummy; } ;
struct xgene_dma_chan {int pending; struct xgene_dma_ring tx_ring; } ;

/* Variables and functions */
 int XGENE_DMA_FLAG_64B_DESC ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xgene_dma_desc_hw*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void xgene_chan_xfer_request(struct xgene_dma_chan *chan,
				    struct xgene_dma_desc_sw *desc_sw)
{
	struct xgene_dma_ring *ring = &chan->tx_ring;
	struct xgene_dma_desc_hw *desc_hw;

	/* Get hw descriptor from DMA tx ring */
	desc_hw = &ring->desc_hw[ring->head];

	/*
	 * Increment the head count to point next
	 * descriptor for next time
	 */
	if (++ring->head == ring->slots)
		ring->head = 0;

	/* Copy prepared sw descriptor data to hw descriptor */
	memcpy(desc_hw, &desc_sw->desc1, sizeof(*desc_hw));

	/*
	 * Check if we have prepared 64B descriptor,
	 * in this case we need one more hw descriptor
	 */
	if (desc_sw->flags & XGENE_DMA_FLAG_64B_DESC) {
		desc_hw = &ring->desc_hw[ring->head];

		if (++ring->head == ring->slots)
			ring->head = 0;

		memcpy(desc_hw, &desc_sw->desc2, sizeof(*desc_hw));
	}

	/* Increment the pending transaction count */
	chan->pending += ((desc_sw->flags &
			  XGENE_DMA_FLAG_64B_DESC) ? 2 : 1);

	/* Notify the hw that we have descriptor ready for execution */
	iowrite32((desc_sw->flags & XGENE_DMA_FLAG_64B_DESC) ?
		  2 : 1, ring->cmd);
}