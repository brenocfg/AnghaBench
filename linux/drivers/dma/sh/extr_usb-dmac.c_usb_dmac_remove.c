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
struct usb_dmac {int n_channels; int /*<<< orphan*/  engine; int /*<<< orphan*/ * channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct usb_dmac* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_dmac_chan_remove (struct usb_dmac*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usb_dmac_remove(struct platform_device *pdev)
{
	struct usb_dmac *dmac = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < dmac->n_channels; ++i)
		usb_dmac_chan_remove(dmac, &dmac->channels[i]);
	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&dmac->engine);

	pm_runtime_disable(&pdev->dev);

	return 0;
}