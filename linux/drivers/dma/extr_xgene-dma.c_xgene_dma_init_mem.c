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
struct xgene_dma {int /*<<< orphan*/  dev; scalar_t__ csr_dma; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ XGENE_DMA_BLK_MEM_RDY ; 
 scalar_t__ XGENE_DMA_BLK_MEM_RDY_VAL ; 
 scalar_t__ XGENE_DMA_MEM_RAM_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xgene_dma_init_ring_mngr (struct xgene_dma*) ; 

__attribute__((used)) static int xgene_dma_init_mem(struct xgene_dma *pdma)
{
	int ret;

	ret = xgene_dma_init_ring_mngr(pdma);
	if (ret)
		return ret;

	/* Bring up memory */
	iowrite32(0x0, pdma->csr_dma + XGENE_DMA_MEM_RAM_SHUTDOWN);

	/* Force a barrier */
	ioread32(pdma->csr_dma + XGENE_DMA_MEM_RAM_SHUTDOWN);

	/* reset may take up to 1ms */
	usleep_range(1000, 1100);

	if (ioread32(pdma->csr_dma + XGENE_DMA_BLK_MEM_RDY)
		!= XGENE_DMA_BLK_MEM_RDY_VAL) {
		dev_err(pdma->dev,
			"Failed to release DMA memory from shutdown\n");
		return -ENODEV;
	}

	return 0;
}