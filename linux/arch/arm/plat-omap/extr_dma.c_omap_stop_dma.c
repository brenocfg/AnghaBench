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
typedef  int /*<<< orphan*/  dma_chan_link_map ;
struct TYPE_4__ {int next_lch; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  DMA_ERRATA_i541 ; 
 int /*<<< orphan*/  DMA_IDLEMODE_NO_IDLE ; 
 int DMA_SYSCONFIG_MIDLEMODE (int /*<<< orphan*/ ) ; 
 int DMA_SYSCONFIG_MIDLEMODE_MASK ; 
 scalar_t__ IS_DMA_ERRATA (int /*<<< orphan*/ ) ; 
 int MAX_LOGICAL_DMA_CH_COUNT ; 
 int /*<<< orphan*/  OCP_SYSCONFIG ; 
 int /*<<< orphan*/  OMAP_DMA_ACTIVE ; 
 int OMAP_DMA_CCR_EN ; 
 int OMAP_DMA_CCR_RD_ACTIVE ; 
 int OMAP_DMA_CCR_SEL_SRC_DST_SYNC ; 
 int OMAP_DMA_CCR_WR_ACTIVE ; 
 int /*<<< orphan*/  disable_lnk (int) ; 
 TYPE_2__* dma_chan ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_disable_channel_irq (int) ; 
 int /*<<< orphan*/  omap_dma_in_1510_mode () ; 
 TYPE_1__* p ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,int) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ,int) ; 
 int stub6 (int /*<<< orphan*/ ,int) ; 
 int stub7 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void omap_stop_dma(int lch)
{
	u32 l;

	/* Disable all interrupts on the channel */
	omap_disable_channel_irq(lch);

	l = p->dma_read(CCR, lch);
	if (IS_DMA_ERRATA(DMA_ERRATA_i541) &&
			(l & OMAP_DMA_CCR_SEL_SRC_DST_SYNC)) {
		int i = 0;
		u32 sys_cf;

		/* Configure No-Standby */
		l = p->dma_read(OCP_SYSCONFIG, lch);
		sys_cf = l;
		l &= ~DMA_SYSCONFIG_MIDLEMODE_MASK;
		l |= DMA_SYSCONFIG_MIDLEMODE(DMA_IDLEMODE_NO_IDLE);
		p->dma_write(l , OCP_SYSCONFIG, 0);

		l = p->dma_read(CCR, lch);
		l &= ~OMAP_DMA_CCR_EN;
		p->dma_write(l, CCR, lch);

		/* Wait for sDMA FIFO drain */
		l = p->dma_read(CCR, lch);
		while (i < 100 && (l & (OMAP_DMA_CCR_RD_ACTIVE |
					OMAP_DMA_CCR_WR_ACTIVE))) {
			udelay(5);
			i++;
			l = p->dma_read(CCR, lch);
		}
		if (i >= 100)
			pr_err("DMA drain did not complete on lch %d\n", lch);
		/* Restore OCP_SYSCONFIG */
		p->dma_write(sys_cf, OCP_SYSCONFIG, lch);
	} else {
		l &= ~OMAP_DMA_CCR_EN;
		p->dma_write(l, CCR, lch);
	}

	/*
	 * Ensure that data transferred by DMA is visible to any access
	 * after DMA has been disabled.  This is important for coherent
	 * DMA regions.
	 */
	mb();

	if (!omap_dma_in_1510_mode() && dma_chan[lch].next_lch != -1) {
		int next_lch, cur_lch = lch;
		char dma_chan_link_map[MAX_LOGICAL_DMA_CH_COUNT];

		memset(dma_chan_link_map, 0, sizeof(dma_chan_link_map));
		do {
			/* The loop case: we've been here already */
			if (dma_chan_link_map[cur_lch])
				break;
			/* Mark the current channel */
			dma_chan_link_map[cur_lch] = 1;

			disable_lnk(cur_lch);

			next_lch = dma_chan[cur_lch].next_lch;
			cur_lch = next_lch;
		} while (next_lch != -1);
	}

	dma_chan[lch].flags &= ~OMAP_DMA_ACTIVE;
}