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
typedef  int u32 ;
struct device_node {int dummy; } ;
struct axi_dmac_chan {int src_type; int dest_type; int src_width; int dest_width; int /*<<< orphan*/  direction; scalar_t__ address_align_mask; } ;

/* Variables and functions */
 int AXI_DMAC_BUS_TYPE_FIFO ; 
 int /*<<< orphan*/  DMA_DEV_TO_DEV ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 int EINVAL ; 
 scalar_t__ axi_dmac_dest_is_mem (struct axi_dmac_chan*) ; 
 scalar_t__ axi_dmac_src_is_mem (struct axi_dmac_chan*) ; 
 scalar_t__ max (int,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int axi_dmac_parse_chan_dt(struct device_node *of_chan,
	struct axi_dmac_chan *chan)
{
	u32 val;
	int ret;

	ret = of_property_read_u32(of_chan, "reg", &val);
	if (ret)
		return ret;

	/* We only support 1 channel for now */
	if (val != 0)
		return -EINVAL;

	ret = of_property_read_u32(of_chan, "adi,source-bus-type", &val);
	if (ret)
		return ret;
	if (val > AXI_DMAC_BUS_TYPE_FIFO)
		return -EINVAL;
	chan->src_type = val;

	ret = of_property_read_u32(of_chan, "adi,destination-bus-type", &val);
	if (ret)
		return ret;
	if (val > AXI_DMAC_BUS_TYPE_FIFO)
		return -EINVAL;
	chan->dest_type = val;

	ret = of_property_read_u32(of_chan, "adi,source-bus-width", &val);
	if (ret)
		return ret;
	chan->src_width = val / 8;

	ret = of_property_read_u32(of_chan, "adi,destination-bus-width", &val);
	if (ret)
		return ret;
	chan->dest_width = val / 8;

	chan->address_align_mask = max(chan->dest_width, chan->src_width) - 1;

	if (axi_dmac_dest_is_mem(chan) && axi_dmac_src_is_mem(chan))
		chan->direction = DMA_MEM_TO_MEM;
	else if (!axi_dmac_dest_is_mem(chan) && axi_dmac_src_is_mem(chan))
		chan->direction = DMA_MEM_TO_DEV;
	else if (axi_dmac_dest_is_mem(chan) && !axi_dmac_src_is_mem(chan))
		chan->direction = DMA_DEV_TO_MEM;
	else
		chan->direction = DMA_DEV_TO_DEV;

	return 0;
}