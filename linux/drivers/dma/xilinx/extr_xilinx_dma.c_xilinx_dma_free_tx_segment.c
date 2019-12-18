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
struct xilinx_dma_chan {int /*<<< orphan*/  free_seg_list; } ;
struct xilinx_axidma_tx_segment {int /*<<< orphan*/  node; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xilinx_dma_clean_hw_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xilinx_dma_free_tx_segment(struct xilinx_dma_chan *chan,
				struct xilinx_axidma_tx_segment *segment)
{
	xilinx_dma_clean_hw_desc(&segment->hw);

	list_add_tail(&segment->node, &chan->free_seg_list);
}