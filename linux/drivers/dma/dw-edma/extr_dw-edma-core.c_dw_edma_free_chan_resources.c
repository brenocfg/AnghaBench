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
struct dw_edma_chan {TYPE_1__* chip; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 struct dw_edma_chan* dchan2dw_edma_chan (struct dma_chan*) ; 
 int dw_edma_device_terminate_all (struct dma_chan*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void dw_edma_free_chan_resources(struct dma_chan *dchan)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(5000);
	struct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	int ret;

	while (time_before(jiffies, timeout)) {
		ret = dw_edma_device_terminate_all(dchan);
		if (!ret)
			break;

		if (time_after_eq(jiffies, timeout))
			return;

		cpu_relax();
	}

	pm_runtime_put(chan->chip->dev);
}