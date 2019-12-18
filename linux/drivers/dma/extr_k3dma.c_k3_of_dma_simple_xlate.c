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
struct of_phandle_args {unsigned int* args; } ;
struct of_dma {struct k3_dma_dev* of_dma_data; } ;
struct k3_dma_dev {unsigned int dma_requests; TYPE_2__* chans; } ;
struct dma_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {TYPE_1__ vc; } ;

/* Variables and functions */
 struct dma_chan* dma_get_slave_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dma_chan *k3_of_dma_simple_xlate(struct of_phandle_args *dma_spec,
						struct of_dma *ofdma)
{
	struct k3_dma_dev *d = ofdma->of_dma_data;
	unsigned int request = dma_spec->args[0];

	if (request >= d->dma_requests)
		return NULL;

	return dma_get_slave_channel(&(d->chans[request].vc.chan));
}