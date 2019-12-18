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
struct fsl_edma_chan {uintptr_t slave_id; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 TYPE_3__ mcf_edma_driver ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 

bool mcf_edma_filter_fn(struct dma_chan *chan, void *param)
{
	if (chan->device->dev->driver == &mcf_edma_driver.driver) {
		struct fsl_edma_chan *mcf_chan = to_fsl_edma_chan(chan);

		return (mcf_chan->slave_id == (uintptr_t)param);
	}

	return false;
}