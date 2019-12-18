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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {TYPE_1__ chan; } ;
struct dw_dma {int (* block2bytes ) (struct dw_dma_chan*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HI ; 
 int /*<<< orphan*/  CTL_LO ; 
 int channel_readl (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dw_dma_chan*,int,int) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 dwc_get_sent(struct dw_dma_chan *dwc)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);
	u32 ctlhi = channel_readl(dwc, CTL_HI);
	u32 ctllo = channel_readl(dwc, CTL_LO);

	return dw->block2bytes(dwc, ctlhi, ctllo >> 4 & 7);
}