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
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct of_dma {struct mmp_pdma_device* of_dma_data; } ;
struct mmp_pdma_device {int /*<<< orphan*/  device; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  drcmr; } ;

/* Variables and functions */
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mmp_pdma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *mmp_pdma_dma_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct mmp_pdma_device *d = ofdma->of_dma_data;
	struct dma_chan *chan;

	chan = dma_get_any_slave_channel(&d->device);
	if (!chan)
		return NULL;

	to_mmp_pdma_chan(chan)->drcmr = dma_spec->args[0];

	return chan;
}