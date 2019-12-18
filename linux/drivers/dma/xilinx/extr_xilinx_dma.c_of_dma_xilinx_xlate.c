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
struct xilinx_dma_device {int nr_channels; TYPE_1__** chan; } ;
struct of_phandle_args {int* args; } ;
struct of_dma {struct xilinx_dma_device* of_dma_data; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  common; } ;

/* Variables and functions */
 struct dma_chan* dma_get_slave_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dma_chan *of_dma_xilinx_xlate(struct of_phandle_args *dma_spec,
						struct of_dma *ofdma)
{
	struct xilinx_dma_device *xdev = ofdma->of_dma_data;
	int chan_id = dma_spec->args[0];

	if (chan_id >= xdev->nr_channels || !xdev->chan[chan_id])
		return NULL;

	return dma_get_slave_channel(&xdev->chan[chan_id]->common);
}