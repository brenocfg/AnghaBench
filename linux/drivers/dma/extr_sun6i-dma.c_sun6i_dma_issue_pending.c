#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct sun6i_vchan {TYPE_1__ vc; int /*<<< orphan*/  node; int /*<<< orphan*/  phy; } ;
struct sun6i_dma_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  pending; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct sun6i_dma_dev* to_sun6i_dma_dev (int /*<<< orphan*/ ) ; 
 struct sun6i_vchan* to_sun6i_vchan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void sun6i_dma_issue_pending(struct dma_chan *chan)
{
	struct sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	struct sun6i_vchan *vchan = to_sun6i_vchan(chan);
	unsigned long flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	if (vchan_issue_pending(&vchan->vc)) {
		spin_lock(&sdev->lock);

		if (!vchan->phy && list_empty(&vchan->node)) {
			list_add_tail(&vchan->node, &sdev->pending);
			tasklet_schedule(&sdev->task);
			dev_dbg(chan2dev(chan), "vchan %p: issued\n",
				&vchan->vc);
		}

		spin_unlock(&sdev->lock);
	} else {
		dev_dbg(chan2dev(chan), "vchan %p: nothing to issue\n",
			&vchan->vc);
	}

	spin_unlock_irqrestore(&vchan->vc.lock, flags);
}