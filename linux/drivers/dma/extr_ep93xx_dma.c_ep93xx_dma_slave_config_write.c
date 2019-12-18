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
typedef  void* u32 ;
struct ep93xx_dma_chan {int /*<<< orphan*/  lock; void* runtime_ctrl; void* runtime_addr; TYPE_1__* edma; } ;
struct dma_slave_config {int src_addr_width; int dst_addr_width; void* dst_addr; void* src_addr; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
struct TYPE_2__ {int /*<<< orphan*/  m2m; } ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 132 
#define  DMA_MEM_TO_DEV 131 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 130 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 
 int EINVAL ; 
 void* M2M_CONTROL_PW_16 ; 
 void* M2M_CONTROL_PW_32 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ep93xx_dma_chan* to_ep93xx_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int ep93xx_dma_slave_config_write(struct dma_chan *chan,
					 enum dma_transfer_direction dir,
					 struct dma_slave_config *config)
{
	struct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	enum dma_slave_buswidth width;
	unsigned long flags;
	u32 addr, ctrl;

	if (!edmac->edma->m2m)
		return -EINVAL;

	switch (dir) {
	case DMA_DEV_TO_MEM:
		width = config->src_addr_width;
		addr = config->src_addr;
		break;

	case DMA_MEM_TO_DEV:
		width = config->dst_addr_width;
		addr = config->dst_addr;
		break;

	default:
		return -EINVAL;
	}

	switch (width) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
		ctrl = 0;
		break;
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		ctrl = M2M_CONTROL_PW_16;
		break;
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		ctrl = M2M_CONTROL_PW_32;
		break;
	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&edmac->lock, flags);
	edmac->runtime_addr = addr;
	edmac->runtime_ctrl = ctrl;
	spin_unlock_irqrestore(&edmac->lock, flags);

	return 0;
}