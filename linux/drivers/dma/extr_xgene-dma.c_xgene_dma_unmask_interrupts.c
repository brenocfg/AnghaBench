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
struct xgene_dma {scalar_t__ csr_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGENE_DMA_INT_ALL_UNMASK ; 
 scalar_t__ XGENE_DMA_INT_MASK ; 
 scalar_t__ XGENE_DMA_RING_INT0_MASK ; 
 scalar_t__ XGENE_DMA_RING_INT1_MASK ; 
 scalar_t__ XGENE_DMA_RING_INT2_MASK ; 
 scalar_t__ XGENE_DMA_RING_INT3_MASK ; 
 scalar_t__ XGENE_DMA_RING_INT4_MASK ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xgene_dma_unmask_interrupts(struct xgene_dma *pdma)
{
	/*
	 * Unmask DMA ring overflow, underflow and
	 * AXI write/read error interrupts
	 */
	iowrite32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT0_MASK);
	iowrite32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT1_MASK);
	iowrite32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT2_MASK);
	iowrite32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT3_MASK);
	iowrite32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT4_MASK);

	/* Unmask DMA error interrupts */
	iowrite32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_INT_MASK);
}