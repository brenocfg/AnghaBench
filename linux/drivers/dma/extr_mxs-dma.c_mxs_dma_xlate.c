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
struct of_phandle_args {int args_count; scalar_t__* args; } ;
struct of_dma {int /*<<< orphan*/  of_node; struct mxs_dma_engine* of_dma_data; } ;
struct mxs_dma_filter_param {scalar_t__ chan_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_mask; } ;
struct mxs_dma_engine {scalar_t__ nr_channels; TYPE_1__ dma_device; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 struct dma_chan* __dma_request_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mxs_dma_filter_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_dma_filter_fn ; 

__attribute__((used)) static struct dma_chan *mxs_dma_xlate(struct of_phandle_args *dma_spec,
			       struct of_dma *ofdma)
{
	struct mxs_dma_engine *mxs_dma = ofdma->of_dma_data;
	dma_cap_mask_t mask = mxs_dma->dma_device.cap_mask;
	struct mxs_dma_filter_param param;

	if (dma_spec->args_count != 1)
		return NULL;

	param.chan_id = dma_spec->args[0];

	if (param.chan_id >= mxs_dma->nr_channels)
		return NULL;

	return __dma_request_channel(&mask, mxs_dma_filter_fn, &param,
				     ofdma->of_node);
}