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
struct xgene_dma_ring {int cfgsize; int size; int /*<<< orphan*/  desc_vaddr; int /*<<< orphan*/  desc_paddr; int /*<<< orphan*/  buf_num; int /*<<< orphan*/  owner; int /*<<< orphan*/  id; scalar_t__ num; TYPE_1__* pdma; } ;
struct xgene_dma_chan {int /*<<< orphan*/  dev; TYPE_1__* pdma; } ;
typedef  enum xgene_dma_ring_cfgsize { ____Placeholder_xgene_dma_ring_cfgsize } xgene_dma_ring_cfgsize ;
struct TYPE_2__ {int /*<<< orphan*/  ring_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XGENE_DMA_RING_ID_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_err (struct xgene_dma_chan*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xgene_dma_get_ring_size (struct xgene_dma_chan*,int) ; 
 int /*<<< orphan*/  xgene_dma_set_ring_cmd (struct xgene_dma_ring*) ; 
 int /*<<< orphan*/  xgene_dma_setup_ring (struct xgene_dma_ring*) ; 

__attribute__((used)) static int xgene_dma_create_ring_one(struct xgene_dma_chan *chan,
				     struct xgene_dma_ring *ring,
				     enum xgene_dma_ring_cfgsize cfgsize)
{
	int ret;

	/* Setup DMA ring descriptor variables */
	ring->pdma = chan->pdma;
	ring->cfgsize = cfgsize;
	ring->num = chan->pdma->ring_num++;
	ring->id = XGENE_DMA_RING_ID_GET(ring->owner, ring->buf_num);

	ret = xgene_dma_get_ring_size(chan, cfgsize);
	if (ret <= 0)
		return ret;
	ring->size = ret;

	/* Allocate memory for DMA ring descriptor */
	ring->desc_vaddr = dma_alloc_coherent(chan->dev, ring->size,
					      &ring->desc_paddr, GFP_KERNEL);
	if (!ring->desc_vaddr) {
		chan_err(chan, "Failed to allocate ring desc\n");
		return -ENOMEM;
	}

	/* Configure and enable DMA ring */
	xgene_dma_set_ring_cmd(ring);
	xgene_dma_setup_ring(ring);

	return 0;
}