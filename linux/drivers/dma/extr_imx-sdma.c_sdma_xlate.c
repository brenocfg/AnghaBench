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
struct TYPE_2__ {int /*<<< orphan*/  cap_mask; } ;
struct sdma_engine {TYPE_1__ dma_device; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; } ;
struct of_dma {int /*<<< orphan*/  of_node; struct sdma_engine* of_dma_data; } ;
struct imx_dma_data {scalar_t__ dma_request2; int /*<<< orphan*/  priority; int /*<<< orphan*/  peripheral_type; int /*<<< orphan*/  dma_request; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 struct dma_chan* __dma_request_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct imx_dma_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_filter_fn ; 

__attribute__((used)) static struct dma_chan *sdma_xlate(struct of_phandle_args *dma_spec,
				   struct of_dma *ofdma)
{
	struct sdma_engine *sdma = ofdma->of_dma_data;
	dma_cap_mask_t mask = sdma->dma_device.cap_mask;
	struct imx_dma_data data;

	if (dma_spec->args_count != 3)
		return NULL;

	data.dma_request = dma_spec->args[0];
	data.peripheral_type = dma_spec->args[1];
	data.priority = dma_spec->args[2];
	/*
	 * init dma_request2 to zero, which is not used by the dts.
	 * For P2P, dma_request2 is init from dma_request_channel(),
	 * chan->private will point to the imx_dma_data, and in
	 * device_alloc_chan_resources(), imx_dma_data.dma_request2 will
	 * be set to sdmac->event_id1.
	 */
	data.dma_request2 = 0;

	return __dma_request_channel(&mask, sdma_filter_fn, &data,
				     ofdma->of_node);
}