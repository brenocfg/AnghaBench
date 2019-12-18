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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_dma_ring {scalar_t__ owner; TYPE_1__* pdma; int /*<<< orphan*/  id; int /*<<< orphan*/  buf_num; } ;
struct TYPE_2__ {scalar_t__ csr_ring; } ;

/* Variables and functions */
 scalar_t__ XGENE_DMA_RING_ID ; 
 scalar_t__ XGENE_DMA_RING_ID_BUF ; 
 int /*<<< orphan*/  XGENE_DMA_RING_ID_SETUP (int /*<<< orphan*/ ) ; 
 scalar_t__ XGENE_DMA_RING_NE_INT_MODE ; 
 int /*<<< orphan*/  XGENE_DMA_RING_NE_INT_MODE_RESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XGENE_DMA_RING_OWNER_CPU ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xgene_dma_clr_ring_state (struct xgene_dma_ring*) ; 

__attribute__((used)) static void xgene_dma_clear_ring(struct xgene_dma_ring *ring)
{
	u32 ring_id, val;

	if (ring->owner == XGENE_DMA_RING_OWNER_CPU) {
		/* Disable DMA Rx ring interrupt */
		val = ioread32(ring->pdma->csr_ring +
			       XGENE_DMA_RING_NE_INT_MODE);
		XGENE_DMA_RING_NE_INT_MODE_RESET(val, ring->buf_num);
		iowrite32(val, ring->pdma->csr_ring +
			  XGENE_DMA_RING_NE_INT_MODE);
	}

	/* Clear DMA ring state */
	ring_id = XGENE_DMA_RING_ID_SETUP(ring->id);
	iowrite32(ring_id, ring->pdma->csr_ring + XGENE_DMA_RING_ID);

	iowrite32(0, ring->pdma->csr_ring + XGENE_DMA_RING_ID_BUF);
	xgene_dma_clr_ring_state(ring);
}