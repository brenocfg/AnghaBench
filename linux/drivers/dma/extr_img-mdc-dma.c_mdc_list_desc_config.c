#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdc_hw_list_desc {int gen_conf; int readport_conf; size_t xfer_size; int ctrl_status; int /*<<< orphan*/ * next_desc; scalar_t__ cmds_done; scalar_t__ node_addr; void* write_addr; void* read_addr; } ;
struct mdc_dma {unsigned int bus_width; unsigned int max_burst_mult; } ;
struct TYPE_2__ {int dst_addr_width; int dst_maxburst; int src_addr_width; int src_maxburst; } ;
struct mdc_chan {int thread; TYPE_1__ config; struct mdc_dma* mdma; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 scalar_t__ IS_ALIGNED (void*,unsigned int) ; 
 int MDC_CONTROL_AND_STATUS_EN ; 
 int MDC_CONTROL_AND_STATUS_LIST_EN ; 
 int MDC_GENERAL_CONFIG_IEN ; 
 int MDC_GENERAL_CONFIG_INC_R ; 
 int MDC_GENERAL_CONFIG_INC_W ; 
 int MDC_GENERAL_CONFIG_LEVEL_INT ; 
 int MDC_GENERAL_CONFIG_LIST_IEN ; 
 int MDC_GENERAL_CONFIG_PHYSICAL_R ; 
 int MDC_GENERAL_CONFIG_PHYSICAL_W ; 
 unsigned int MDC_READ_PORT_CONFIG_BURST_SIZE_SHIFT ; 
 int MDC_READ_PORT_CONFIG_DREQ_ENABLE ; 
 int MDC_READ_PORT_CONFIG_RTHREAD_SHIFT ; 
 int MDC_READ_PORT_CONFIG_STHREAD_SHIFT ; 
 int MDC_READ_PORT_CONFIG_WTHREAD_SHIFT ; 
 int /*<<< orphan*/  mdc_set_read_width (struct mdc_hw_list_desc*,int) ; 
 int /*<<< orphan*/  mdc_set_write_width (struct mdc_hw_list_desc*,int) ; 
 unsigned int min (unsigned int,int) ; 

__attribute__((used)) static void mdc_list_desc_config(struct mdc_chan *mchan,
				 struct mdc_hw_list_desc *ldesc,
				 enum dma_transfer_direction dir,
				 dma_addr_t src, dma_addr_t dst, size_t len)
{
	struct mdc_dma *mdma = mchan->mdma;
	unsigned int max_burst, burst_size;

	ldesc->gen_conf = MDC_GENERAL_CONFIG_IEN | MDC_GENERAL_CONFIG_LIST_IEN |
		MDC_GENERAL_CONFIG_LEVEL_INT | MDC_GENERAL_CONFIG_PHYSICAL_W |
		MDC_GENERAL_CONFIG_PHYSICAL_R;
	ldesc->readport_conf =
		(mchan->thread << MDC_READ_PORT_CONFIG_STHREAD_SHIFT) |
		(mchan->thread << MDC_READ_PORT_CONFIG_RTHREAD_SHIFT) |
		(mchan->thread << MDC_READ_PORT_CONFIG_WTHREAD_SHIFT);
	ldesc->read_addr = src;
	ldesc->write_addr = dst;
	ldesc->xfer_size = len - 1;
	ldesc->node_addr = 0;
	ldesc->cmds_done = 0;
	ldesc->ctrl_status = MDC_CONTROL_AND_STATUS_LIST_EN |
		MDC_CONTROL_AND_STATUS_EN;
	ldesc->next_desc = NULL;

	if (IS_ALIGNED(dst, mdma->bus_width) &&
	    IS_ALIGNED(src, mdma->bus_width))
		max_burst = mdma->bus_width * mdma->max_burst_mult;
	else
		max_burst = mdma->bus_width * (mdma->max_burst_mult - 1);

	if (dir == DMA_MEM_TO_DEV) {
		ldesc->gen_conf |= MDC_GENERAL_CONFIG_INC_R;
		ldesc->readport_conf |= MDC_READ_PORT_CONFIG_DREQ_ENABLE;
		mdc_set_read_width(ldesc, mdma->bus_width);
		mdc_set_write_width(ldesc, mchan->config.dst_addr_width);
		burst_size = min(max_burst, mchan->config.dst_maxburst *
				 mchan->config.dst_addr_width);
	} else if (dir == DMA_DEV_TO_MEM) {
		ldesc->gen_conf |= MDC_GENERAL_CONFIG_INC_W;
		ldesc->readport_conf |= MDC_READ_PORT_CONFIG_DREQ_ENABLE;
		mdc_set_read_width(ldesc, mchan->config.src_addr_width);
		mdc_set_write_width(ldesc, mdma->bus_width);
		burst_size = min(max_burst, mchan->config.src_maxburst *
				 mchan->config.src_addr_width);
	} else {
		ldesc->gen_conf |= MDC_GENERAL_CONFIG_INC_R |
			MDC_GENERAL_CONFIG_INC_W;
		mdc_set_read_width(ldesc, mdma->bus_width);
		mdc_set_write_width(ldesc, mdma->bus_width);
		burst_size = max_burst;
	}
	ldesc->readport_conf |= (burst_size - 1) <<
		MDC_READ_PORT_CONFIG_BURST_SIZE_SHIFT;
}