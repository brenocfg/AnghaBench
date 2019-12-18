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
struct dw_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DMA_IS_PAUSED ; 
 int /*<<< orphan*/  dwc_chan_resume (struct dw_dma_chan*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int dwc_resume(struct dma_chan *chan)
{
	struct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	unsigned long		flags;

	spin_lock_irqsave(&dwc->lock, flags);

	if (test_bit(DW_DMA_IS_PAUSED, &dwc->flags))
		dwc_chan_resume(dwc, false);

	spin_unlock_irqrestore(&dwc->lock, flags);

	return 0;
}