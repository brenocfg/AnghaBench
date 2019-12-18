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
struct fsl_edma_engine {int n_chans; struct fsl_edma_chan* chans; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fsl_edma_chan {TYPE_1__ vchan; int /*<<< orphan*/  pm_state; int /*<<< orphan*/  idle; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPENDED ; 
 struct fsl_edma_engine* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  fsl_edma_chan_mux (struct fsl_edma_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsl_edma_disable_request (struct fsl_edma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fsl_edma_suspend_late(struct device *dev)
{
	struct fsl_edma_engine *fsl_edma = dev_get_drvdata(dev);
	struct fsl_edma_chan *fsl_chan;
	unsigned long flags;
	int i;

	for (i = 0; i < fsl_edma->n_chans; i++) {
		fsl_chan = &fsl_edma->chans[i];
		spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
		/* Make sure chan is idle or will force disable. */
		if (unlikely(!fsl_chan->idle)) {
			dev_warn(dev, "WARN: There is non-idle channel.");
			fsl_edma_disable_request(fsl_chan);
			fsl_edma_chan_mux(fsl_chan, 0, false);
		}

		fsl_chan->pm_state = SUSPENDED;
		spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	}

	return 0;
}