#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLNK_CTRL ; 
 int /*<<< orphan*/  OMAP_DMA_ACTIVE ; 
 TYPE_2__* dma_chan ; 
 scalar_t__ dma_omap1 () ; 
 scalar_t__ dma_omap2plus () ; 
 int /*<<< orphan*/  omap_disable_channel_irq (int) ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void disable_lnk(int lch)
{
	u32 l;

	l = p->dma_read(CLNK_CTRL, lch);

	/* Disable interrupts */
	omap_disable_channel_irq(lch);

	if (dma_omap1()) {
		/* Set the STOP_LNK bit */
		l |= 1 << 14;
	}

	if (dma_omap2plus()) {
		/* Clear the ENABLE_LNK bit */
		l &= ~(1 << 15);
	}

	p->dma_write(l, CLNK_CTRL, lch);
	dma_chan[lch].flags &= ~OMAP_DMA_ACTIVE;
}