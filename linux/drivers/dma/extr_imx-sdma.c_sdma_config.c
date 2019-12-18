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
struct sdma_channel {scalar_t__ event_id0; scalar_t__ event_id1; TYPE_1__* sdma; int /*<<< orphan*/  slave_config; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {scalar_t__ num_events; } ;
struct TYPE_3__ {TYPE_2__* drvdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 int /*<<< orphan*/  sdma_event_enable (struct sdma_channel*,scalar_t__) ; 
 struct sdma_channel* to_sdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sdma_config(struct dma_chan *chan,
		       struct dma_slave_config *dmaengine_cfg)
{
	struct sdma_channel *sdmac = to_sdma_chan(chan);

	memcpy(&sdmac->slave_config, dmaengine_cfg, sizeof(*dmaengine_cfg));

	/* Set ENBLn earlier to make sure dma request triggered after that */
	if (sdmac->event_id0) {
		if (sdmac->event_id0 >= sdmac->sdma->drvdata->num_events)
			return -EINVAL;
		sdma_event_enable(sdmac, sdmac->event_id0);
	}

	if (sdmac->event_id1) {
		if (sdmac->event_id1 >= sdmac->sdma->drvdata->num_events)
			return -EINVAL;
		sdma_event_enable(sdmac, sdmac->event_id1);
	}

	return 0;
}