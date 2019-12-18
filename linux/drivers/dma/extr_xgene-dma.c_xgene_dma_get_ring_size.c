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
struct xgene_dma_chan {int dummy; } ;
typedef  enum xgene_dma_ring_cfgsize { ____Placeholder_xgene_dma_ring_cfgsize } xgene_dma_ring_cfgsize ;

/* Variables and functions */
 int EINVAL ; 
#define  XGENE_DMA_RING_CFG_SIZE_16KB 132 
#define  XGENE_DMA_RING_CFG_SIZE_2KB 131 
#define  XGENE_DMA_RING_CFG_SIZE_512B 130 
#define  XGENE_DMA_RING_CFG_SIZE_512KB 129 
#define  XGENE_DMA_RING_CFG_SIZE_64KB 128 
 int /*<<< orphan*/  chan_err (struct xgene_dma_chan*,char*,int) ; 

__attribute__((used)) static int xgene_dma_get_ring_size(struct xgene_dma_chan *chan,
				   enum xgene_dma_ring_cfgsize cfgsize)
{
	int size;

	switch (cfgsize) {
	case XGENE_DMA_RING_CFG_SIZE_512B:
		size = 0x200;
		break;
	case XGENE_DMA_RING_CFG_SIZE_2KB:
		size = 0x800;
		break;
	case XGENE_DMA_RING_CFG_SIZE_16KB:
		size = 0x4000;
		break;
	case XGENE_DMA_RING_CFG_SIZE_64KB:
		size = 0x10000;
		break;
	case XGENE_DMA_RING_CFG_SIZE_512KB:
		size = 0x80000;
		break;
	default:
		chan_err(chan, "Unsupported cfg ring size %d\n", cfgsize);
		return -EINVAL;
	}

	return size;
}