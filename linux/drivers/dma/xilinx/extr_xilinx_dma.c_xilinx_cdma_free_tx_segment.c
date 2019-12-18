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
struct xilinx_dma_chan {int /*<<< orphan*/  desc_pool; } ;
struct xilinx_cdma_tx_segment {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct xilinx_cdma_tx_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xilinx_cdma_free_tx_segment(struct xilinx_dma_chan *chan,
				struct xilinx_cdma_tx_segment *segment)
{
	dma_pool_free(chan->desc_pool, segment, segment->phys);
}