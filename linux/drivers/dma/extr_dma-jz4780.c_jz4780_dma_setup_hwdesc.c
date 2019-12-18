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
typedef  size_t uint32_t ;
struct jz4780_dma_hwdesc {size_t dcm; size_t dsa; size_t dta; size_t dtc; } ;
struct dma_slave_config {size_t dst_addr; size_t dst_addr_width; size_t dst_maxburst; size_t src_addr; size_t src_addr_width; size_t src_maxburst; } ;
struct jz4780_dma_chan {size_t transfer_shift; struct dma_slave_config config; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int DMA_MEM_TO_DEV ; 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 130 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 
 int EINVAL ; 
 size_t JZ_DMA_DCM_DAI ; 
 size_t JZ_DMA_DCM_DP_SHIFT ; 
 size_t JZ_DMA_DCM_SAI ; 
 size_t JZ_DMA_DCM_SP_SHIFT ; 
 size_t JZ_DMA_DCM_TSZ_SHIFT ; 
 size_t JZ_DMA_WIDTH_32_BIT ; 
 size_t jz4780_dma_transfer_size (struct jz4780_dma_chan*,size_t,size_t*) ; 

__attribute__((used)) static int jz4780_dma_setup_hwdesc(struct jz4780_dma_chan *jzchan,
	struct jz4780_dma_hwdesc *desc, dma_addr_t addr, size_t len,
	enum dma_transfer_direction direction)
{
	struct dma_slave_config *config = &jzchan->config;
	uint32_t width, maxburst, tsz;

	if (direction == DMA_MEM_TO_DEV) {
		desc->dcm = JZ_DMA_DCM_SAI;
		desc->dsa = addr;
		desc->dta = config->dst_addr;

		width = config->dst_addr_width;
		maxburst = config->dst_maxburst;
	} else {
		desc->dcm = JZ_DMA_DCM_DAI;
		desc->dsa = config->src_addr;
		desc->dta = addr;

		width = config->src_addr_width;
		maxburst = config->src_maxburst;
	}

	/*
	 * This calculates the maximum transfer size that can be used with the
	 * given address, length, width and maximum burst size. The address
	 * must be aligned to the transfer size, the total length must be
	 * divisible by the transfer size, and we must not use more than the
	 * maximum burst specified by the user.
	 */
	tsz = jz4780_dma_transfer_size(jzchan, addr | len | (width * maxburst),
				       &jzchan->transfer_shift);

	switch (width) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		break;
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		width = JZ_DMA_WIDTH_32_BIT;
		break;
	default:
		return -EINVAL;
	}

	desc->dcm |= tsz << JZ_DMA_DCM_TSZ_SHIFT;
	desc->dcm |= width << JZ_DMA_DCM_SP_SHIFT;
	desc->dcm |= width << JZ_DMA_DCM_DP_SHIFT;

	desc->dtc = len >> jzchan->transfer_shift;
	return 0;
}