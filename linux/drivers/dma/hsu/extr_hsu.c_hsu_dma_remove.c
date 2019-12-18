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
struct hsu_dma_chip {struct hsu_dma* hsu; } ;
struct TYPE_2__ {int /*<<< orphan*/  task; } ;
struct hsu_dma_chan {TYPE_1__ vchan; } ;
struct hsu_dma {unsigned short nr_channels; struct hsu_dma_chan* chan; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int hsu_dma_remove(struct hsu_dma_chip *chip)
{
	struct hsu_dma *hsu = chip->hsu;
	unsigned short i;

	dma_async_device_unregister(&hsu->dma);

	for (i = 0; i < hsu->nr_channels; i++) {
		struct hsu_dma_chan *hsuc = &hsu->chan[i];

		tasklet_kill(&hsuc->vchan.task);
	}

	return 0;
}