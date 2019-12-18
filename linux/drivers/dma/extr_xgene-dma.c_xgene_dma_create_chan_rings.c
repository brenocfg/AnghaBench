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
struct xgene_dma_ring {int /*<<< orphan*/  slots; int /*<<< orphan*/  desc_vaddr; int /*<<< orphan*/  num; int /*<<< orphan*/  id; int /*<<< orphan*/  dst_ring_num; scalar_t__ buf_num; int /*<<< orphan*/  owner; } ;
struct xgene_dma_chan {int /*<<< orphan*/  max_outstanding; scalar_t__ id; struct xgene_dma_ring tx_ring; struct xgene_dma_ring rx_ring; } ;

/* Variables and functions */
 scalar_t__ XGENE_DMA_BUFNUM ; 
 scalar_t__ XGENE_DMA_CPU_BUFNUM ; 
 int /*<<< orphan*/  XGENE_DMA_RING_CFG_SIZE_64KB ; 
 int /*<<< orphan*/  XGENE_DMA_RING_DST_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_OWNER_CPU ; 
 int /*<<< orphan*/  XGENE_DMA_RING_OWNER_DMA ; 
 int /*<<< orphan*/  chan_dbg (struct xgene_dma_chan*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xgene_dma_create_ring_one (struct xgene_dma_chan*,struct xgene_dma_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_dma_delete_ring_one (struct xgene_dma_ring*) ; 

__attribute__((used)) static int xgene_dma_create_chan_rings(struct xgene_dma_chan *chan)
{
	struct xgene_dma_ring *rx_ring = &chan->rx_ring;
	struct xgene_dma_ring *tx_ring = &chan->tx_ring;
	int ret;

	/* Create DMA Rx ring descriptor */
	rx_ring->owner = XGENE_DMA_RING_OWNER_CPU;
	rx_ring->buf_num = XGENE_DMA_CPU_BUFNUM + chan->id;

	ret = xgene_dma_create_ring_one(chan, rx_ring,
					XGENE_DMA_RING_CFG_SIZE_64KB);
	if (ret)
		return ret;

	chan_dbg(chan, "Rx ring id 0x%X num %d desc 0x%p\n",
		 rx_ring->id, rx_ring->num, rx_ring->desc_vaddr);

	/* Create DMA Tx ring descriptor */
	tx_ring->owner = XGENE_DMA_RING_OWNER_DMA;
	tx_ring->buf_num = XGENE_DMA_BUFNUM + chan->id;

	ret = xgene_dma_create_ring_one(chan, tx_ring,
					XGENE_DMA_RING_CFG_SIZE_64KB);
	if (ret) {
		xgene_dma_delete_ring_one(rx_ring);
		return ret;
	}

	tx_ring->dst_ring_num = XGENE_DMA_RING_DST_ID(rx_ring->num);

	chan_dbg(chan,
		 "Tx ring id 0x%X num %d desc 0x%p\n",
		 tx_ring->id, tx_ring->num, tx_ring->desc_vaddr);

	/* Set the max outstanding request possible to this channel */
	chan->max_outstanding = tx_ring->slots;

	return ret;
}