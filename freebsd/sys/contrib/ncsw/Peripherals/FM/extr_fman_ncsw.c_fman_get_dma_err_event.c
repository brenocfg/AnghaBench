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
struct fman_dma_regs {int /*<<< orphan*/  fmdmsr; int /*<<< orphan*/  fmdmmr; } ;

/* Variables and functions */
 int DMA_MODE_BER ; 
 int DMA_MODE_ECC ; 
 int DMA_STATUS_BUS_ERR ; 
 int DMA_STATUS_FM_SPDAT_ECC ; 
 int DMA_STATUS_FM_WRITE_ECC ; 
 int DMA_STATUS_READ_ECC ; 
 int DMA_STATUS_SYSTEM_WRITE_ECC ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

uint32_t fman_get_dma_err_event(struct fman_dma_regs *dma_rg)
{
	uint32_t status, mask;

	status = ioread32be(&dma_rg->fmdmsr);
	mask = ioread32be(&dma_rg->fmdmmr);

	/* clear DMA_STATUS_BUS_ERR if mask has no DMA_MODE_BER */
	if ((mask & DMA_MODE_BER) != DMA_MODE_BER)
		status &= ~DMA_STATUS_BUS_ERR;

	/* clear relevant bits if mask has no DMA_MODE_ECC */
	if ((mask & DMA_MODE_ECC) != DMA_MODE_ECC)
		status &= ~(DMA_STATUS_FM_SPDAT_ECC |
		        DMA_STATUS_READ_ECC |
				DMA_STATUS_SYSTEM_WRITE_ECC |
				DMA_STATUS_FM_WRITE_ECC);

	/* clear set events */
	iowrite32be(status, &dma_rg->fmdmsr);

	return status;
}