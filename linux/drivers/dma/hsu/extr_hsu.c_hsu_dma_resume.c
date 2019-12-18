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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct hsu_dma_chan {TYPE_1__ vchan; TYPE_2__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ DMA_IN_PROGRESS ; 
 scalar_t__ DMA_PAUSED ; 
 int /*<<< orphan*/  hsu_chan_enable (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hsu_dma_chan* to_hsu_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int hsu_dma_resume(struct dma_chan *chan)
{
	struct hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	if (hsuc->desc && hsuc->desc->status == DMA_PAUSED) {
		hsuc->desc->status = DMA_IN_PROGRESS;
		hsu_chan_enable(hsuc);
	}
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	return 0;
}