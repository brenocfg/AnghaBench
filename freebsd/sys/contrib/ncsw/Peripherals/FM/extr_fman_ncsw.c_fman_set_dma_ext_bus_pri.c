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
 int DMA_MODE_BUS_PRI_SHIFT ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_dma_ext_bus_pri(struct fman_dma_regs *dma_rg, uint32_t pri)
{
	uint32_t tmp;

	tmp = ioread32be(&dma_rg->fmdmmr) |
			(pri << DMA_MODE_BUS_PRI_SHIFT);

	iowrite32be(tmp, &dma_rg->fmdmmr);
}