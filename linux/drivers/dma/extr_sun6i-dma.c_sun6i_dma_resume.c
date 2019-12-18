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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_issued; } ;
struct sun6i_vchan {TYPE_1__ vc; int /*<<< orphan*/  node; struct sun6i_pchan* phy; } ;
struct sun6i_pchan {scalar_t__ base; } ;
struct sun6i_dma_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_PAUSE ; 
 int /*<<< orphan*/  DMA_CHAN_PAUSE_RESUME ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sun6i_dma_dev* to_sun6i_dma_dev (int /*<<< orphan*/ ) ; 
 struct sun6i_vchan* to_sun6i_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun6i_dma_resume(struct dma_chan *chan)
{
	struct sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	struct sun6i_vchan *vchan = to_sun6i_vchan(chan);
	struct sun6i_pchan *pchan = vchan->phy;
	unsigned long flags;

	dev_dbg(chan2dev(chan), "vchan %p: resume\n", &vchan->vc);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	if (pchan) {
		writel(DMA_CHAN_PAUSE_RESUME,
		       pchan->base + DMA_CHAN_PAUSE);
	} else if (!list_empty(&vchan->vc.desc_issued)) {
		spin_lock(&sdev->lock);
		list_add_tail(&vchan->node, &sdev->pending);
		spin_unlock(&sdev->lock);
	}

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	return 0;
}