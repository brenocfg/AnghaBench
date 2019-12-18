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
struct dma_chan {int /*<<< orphan*/ * route_data; TYPE_2__* router; TYPE_1__* device; int /*<<< orphan*/  client_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* route_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* device_free_chan_resources ) (struct dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dma_chan_to_owner (struct dma_chan*) ; 
 int /*<<< orphan*/  dmaengine_synchronize (struct dma_chan*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dma_chan*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_chan_put(struct dma_chan *chan)
{
	/* This channel is not in use, bail out */
	if (!chan->client_count)
		return;

	chan->client_count--;
	module_put(dma_chan_to_owner(chan));

	/* This channel is not in use anymore, free it */
	if (!chan->client_count && chan->device->device_free_chan_resources) {
		/* Make sure all operations have completed */
		dmaengine_synchronize(chan);
		chan->device->device_free_chan_resources(chan);
	}

	/* If the channel is used via a DMA request router, free the mapping */
	if (chan->router && chan->router->route_free) {
		chan->router->route_free(chan->router->dev, chan->route_data);
		chan->router = NULL;
		chan->route_data = NULL;
	}
}