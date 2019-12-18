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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct hidma_dev {TYPE_2__ ddev; int /*<<< orphan*/  lldev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct hidma_chan {int paused; TYPE_1__ chan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hidma_ll_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct hidma_chan* to_hidma_chan (struct dma_chan*) ; 
 struct hidma_dev* to_hidma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidma_resume(struct dma_chan *chan)
{
	struct hidma_chan *mchan;
	struct hidma_dev *dmadev;
	int rc = 0;

	mchan = to_hidma_chan(chan);
	dmadev = to_hidma_dev(mchan->chan.device);
	if (mchan->paused) {
		pm_runtime_get_sync(dmadev->ddev.dev);
		rc = hidma_ll_enable(dmadev->lldev);
		if (!rc)
			mchan->paused = false;
		else
			dev_err(dmadev->ddev.dev,
				"failed to resume the channel");
		pm_runtime_mark_last_busy(dmadev->ddev.dev);
		pm_runtime_put_autosuspend(dmadev->ddev.dev);
	}
	return rc;
}