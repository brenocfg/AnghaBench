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
 int /*<<< orphan*/  xilinx_dma_chan_desc_cleanup (struct xilinx_dma_chan*) ; 

__attribute__((used)) static void xilinx_dma_do_tasklet(unsigned long data)
{
	struct xilinx_dma_chan *chan = (struct xilinx_dma_chan *)data;

	xilinx_dma_chan_desc_cleanup(chan);
}