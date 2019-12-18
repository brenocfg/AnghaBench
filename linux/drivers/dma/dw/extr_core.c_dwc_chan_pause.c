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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {int /*<<< orphan*/  flags; TYPE_1__ chan; } ;
struct dw_dma {int /*<<< orphan*/  (* suspend_chan ) (struct dw_dma_chan*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LO ; 
 int DWC_CFGL_FIFO_EMPTY ; 
 int /*<<< orphan*/  DW_DMA_IS_PAUSED ; 
 int channel_readl (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dw_dma_chan*,int) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dwc_chan_pause(struct dw_dma_chan *dwc, bool drain)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);
	unsigned int		count = 20;	/* timeout iterations */

	dw->suspend_chan(dwc, drain);

	while (!(channel_readl(dwc, CFG_LO) & DWC_CFGL_FIFO_EMPTY) && count--)
		udelay(2);

	set_bit(DW_DMA_IS_PAUSED, &dwc->flags);
}