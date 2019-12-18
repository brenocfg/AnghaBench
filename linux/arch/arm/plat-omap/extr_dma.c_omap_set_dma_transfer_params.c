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
typedef  int u16 ;
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CCR2 ; 
 int /*<<< orphan*/  CEN ; 
 int /*<<< orphan*/  CFN ; 
 int /*<<< orphan*/  CSDP ; 
 int OMAP_DMA_DST_SYNC_PREFETCH ; 
 int OMAP_DMA_SYNC_BLOCK ; 
 int OMAP_DMA_SYNC_FRAME ; 
 scalar_t__ dma_omap1 () ; 
 scalar_t__ dma_omap2plus () ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ,int) ; 
 int stub5 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ,int) ; 
 int stub7 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ,int) ; 

void omap_set_dma_transfer_params(int lch, int data_type, int elem_count,
				  int frame_count, int sync_mode,
				  int dma_trigger, int src_or_dst_synch)
{
	u32 l;

	l = p->dma_read(CSDP, lch);
	l &= ~0x03;
	l |= data_type;
	p->dma_write(l, CSDP, lch);

	if (dma_omap1()) {
		u16 ccr;

		ccr = p->dma_read(CCR, lch);
		ccr &= ~(1 << 5);
		if (sync_mode == OMAP_DMA_SYNC_FRAME)
			ccr |= 1 << 5;
		p->dma_write(ccr, CCR, lch);

		ccr = p->dma_read(CCR2, lch);
		ccr &= ~(1 << 2);
		if (sync_mode == OMAP_DMA_SYNC_BLOCK)
			ccr |= 1 << 2;
		p->dma_write(ccr, CCR2, lch);
	}

	if (dma_omap2plus() && dma_trigger) {
		u32 val;

		val = p->dma_read(CCR, lch);

		/* DMA_SYNCHRO_CONTROL_UPPER depends on the channel number */
		val &= ~((1 << 23) | (3 << 19) | 0x1f);
		val |= (dma_trigger & ~0x1f) << 14;
		val |= dma_trigger & 0x1f;

		if (sync_mode & OMAP_DMA_SYNC_FRAME)
			val |= 1 << 5;
		else
			val &= ~(1 << 5);

		if (sync_mode & OMAP_DMA_SYNC_BLOCK)
			val |= 1 << 18;
		else
			val &= ~(1 << 18);

		if (src_or_dst_synch == OMAP_DMA_DST_SYNC_PREFETCH) {
			val &= ~(1 << 24);	/* dest synch */
			val |= (1 << 23);	/* Prefetch */
		} else if (src_or_dst_synch) {
			val |= 1 << 24;		/* source synch */
		} else {
			val &= ~(1 << 24);	/* dest synch */
		}
		p->dma_write(val, CCR, lch);
	}

	p->dma_write(elem_count, CEN, lch);
	p->dma_write(frame_count, CFN, lch);
}