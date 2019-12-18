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
struct xilinx_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XILINX_DMA_DMAXR_ALL_IRQ_MASK ; 
 int /*<<< orphan*/  XILINX_DMA_REG_DMACR ; 
 int /*<<< orphan*/  dma_ctrl_set (struct xilinx_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xilinx_dma_reset (struct xilinx_dma_chan*) ; 

__attribute__((used)) static int xilinx_dma_chan_reset(struct xilinx_dma_chan *chan)
{
	int err;

	/* Reset VDMA */
	err = xilinx_dma_reset(chan);
	if (err)
		return err;

	/* Enable interrupts */
	dma_ctrl_set(chan, XILINX_DMA_REG_DMACR,
		      XILINX_DMA_DMAXR_ALL_IRQ_MASK);

	return 0;
}