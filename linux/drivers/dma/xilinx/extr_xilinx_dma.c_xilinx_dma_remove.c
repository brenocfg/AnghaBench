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
struct xilinx_dma_device {int nr_channels; scalar_t__* chan; int /*<<< orphan*/  common; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct xilinx_dma_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xdma_disable_allclks (struct xilinx_dma_device*) ; 
 int /*<<< orphan*/  xilinx_dma_chan_remove (scalar_t__) ; 

__attribute__((used)) static int xilinx_dma_remove(struct platform_device *pdev)
{
	struct xilinx_dma_device *xdev = platform_get_drvdata(pdev);
	int i;

	of_dma_controller_free(pdev->dev.of_node);

	dma_async_device_unregister(&xdev->common);

	for (i = 0; i < xdev->nr_channels; i++)
		if (xdev->chan[i])
			xilinx_dma_chan_remove(xdev->chan[i]);

	xdma_disable_allclks(xdev);

	return 0;
}