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
struct dw_edma_chan {scalar_t__ status; TYPE_1__* chip; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ EDMA_ST_IDLE ; 
 struct dw_edma_chan* dchan2dw_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_edma_alloc_chan_resources(struct dma_chan *dchan)
{
	struct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	if (chan->status != EDMA_ST_IDLE)
		return -EBUSY;

	pm_runtime_get(chan->chip->dev);

	return 0;
}