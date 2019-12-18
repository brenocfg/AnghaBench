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
typedef  int uint32_t ;
struct fman_dma_regs {int /*<<< orphan*/  fmdmmr; } ;

/* Variables and functions */
 scalar_t__ DMA_MODE_EMER_READ ; 
 scalar_t__ DMA_MODE_EMER_WRITE ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_dma_emergency(struct fman_dma_regs *dma_rg,
				bool is_write,
				bool enable)
{
	uint32_t msk;

	msk = (uint32_t)(is_write ? DMA_MODE_EMER_WRITE : DMA_MODE_EMER_READ);

	if (enable)
		iowrite32be(ioread32be(&dma_rg->fmdmmr) | msk,
				&dma_rg->fmdmmr);
	else /* disable */
		iowrite32be(ioread32be(&dma_rg->fmdmmr) & ~msk,
				&dma_rg->fmdmmr);
}