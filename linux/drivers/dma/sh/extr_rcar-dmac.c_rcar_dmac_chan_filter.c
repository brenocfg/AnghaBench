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
struct rcar_dmac {int /*<<< orphan*/  modules; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ device_config; } ;

/* Variables and functions */
 scalar_t__ rcar_dmac_device_config ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_dmac* to_rcar_dmac (TYPE_1__*) ; 

__attribute__((used)) static bool rcar_dmac_chan_filter(struct dma_chan *chan, void *arg)
{
	struct rcar_dmac *dmac = to_rcar_dmac(chan->device);
	struct of_phandle_args *dma_spec = arg;

	/*
	 * FIXME: Using a filter on OF platforms is a nonsense. The OF xlate
	 * function knows from which device it wants to allocate a channel from,
	 * and would be perfectly capable of selecting the channel it wants.
	 * Forcing it to call dma_request_channel() and iterate through all
	 * channels from all controllers is just pointless.
	 */
	if (chan->device->device_config != rcar_dmac_device_config)
		return false;

	return !test_and_set_bit(dma_spec->args[0], dmac->modules);
}