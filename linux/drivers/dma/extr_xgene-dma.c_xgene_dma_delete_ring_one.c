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
struct xgene_dma_ring {int /*<<< orphan*/ * desc_vaddr; int /*<<< orphan*/  desc_paddr; int /*<<< orphan*/  size; TYPE_1__* pdma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_dma_clear_ring (struct xgene_dma_ring*) ; 

__attribute__((used)) static void xgene_dma_delete_ring_one(struct xgene_dma_ring *ring)
{
	/* Clear DMA ring configurations */
	xgene_dma_clear_ring(ring);

	/* De-allocate DMA ring descriptor */
	if (ring->desc_vaddr) {
		dma_free_coherent(ring->pdma->dev, ring->size,
				  ring->desc_vaddr, ring->desc_paddr);
		ring->desc_vaddr = NULL;
	}
}