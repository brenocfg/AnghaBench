#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct edma_chan {unsigned int ch_num; int hw_triggered; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 TYPE_3__ edma_driver ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 

__attribute__((used)) static bool edma_filter_fn(struct dma_chan *chan, void *param)
{
	bool match = false;

	if (chan->device->dev->driver == &edma_driver.driver) {
		struct edma_chan *echan = to_edma_chan(chan);
		unsigned ch_req = *(unsigned *)param;
		if (ch_req == echan->ch_num) {
			/* The channel is going to be used as HW synchronized */
			echan->hw_triggered = true;
			match = true;
		}
	}
	return match;
}