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
typedef  int u32 ;
typedef  enum omap_dma_burst_mode { ____Placeholder_omap_dma_burst_mode } omap_dma_burst_mode ;
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CSDP ; 
#define  OMAP_DMA_DATA_BURST_16 131 
#define  OMAP_DMA_DATA_BURST_4 130 
#define  OMAP_DMA_DATA_BURST_8 129 
#define  OMAP_DMA_DATA_BURST_DIS 128 
 int /*<<< orphan*/  dma_omap2plus () ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 

void omap_set_dma_src_burst_mode(int lch, enum omap_dma_burst_mode burst_mode)
{
	unsigned int burst = 0;
	u32 l;

	l = p->dma_read(CSDP, lch);
	l &= ~(0x03 << 7);

	switch (burst_mode) {
	case OMAP_DMA_DATA_BURST_DIS:
		break;
	case OMAP_DMA_DATA_BURST_4:
		if (dma_omap2plus())
			burst = 0x1;
		else
			burst = 0x2;
		break;
	case OMAP_DMA_DATA_BURST_8:
		if (dma_omap2plus()) {
			burst = 0x2;
			break;
		}
		/*
		 * not supported by current hardware on OMAP1
		 * w |= (0x03 << 7);
		 */
		/* fall through */
	case OMAP_DMA_DATA_BURST_16:
		if (dma_omap2plus()) {
			burst = 0x3;
			break;
		}
		/* OMAP1 don't support burst 16 */
		/* fall through */
	default:
		BUG();
	}

	l |= (burst << 7);
	p->dma_write(l, CSDP, lch);
}