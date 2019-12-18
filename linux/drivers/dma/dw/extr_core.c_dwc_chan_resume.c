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
struct dw_dma {int /*<<< orphan*/  (* resume_chan ) (struct dw_dma_chan*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DMA_IS_PAUSED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dw_dma_chan*,int) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwc_chan_resume(struct dw_dma_chan *dwc, bool drain)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);

	dw->resume_chan(dwc, drain);

	clear_bit(DW_DMA_IS_PAUSED, &dwc->flags);
}