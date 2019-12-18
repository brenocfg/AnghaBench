#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sata_dwc_device_port {int /*<<< orphan*/  chan; struct sata_dwc_device* hsdev; } ;
struct sata_dwc_device {struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dma_request_chan (struct device*,char*) ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int sata_dwc_dma_get_channel_old (struct sata_dwc_device_port*) ; 

__attribute__((used)) static int sata_dwc_dma_get_channel(struct sata_dwc_device_port *hsdevp)
{
	struct sata_dwc_device *hsdev = hsdevp->hsdev;
	struct device *dev = hsdev->dev;

#ifdef CONFIG_SATA_DWC_OLD_DMA
	if (!of_find_property(dev->of_node, "dmas", NULL))
		return sata_dwc_dma_get_channel_old(hsdevp);
#endif

	hsdevp->chan = dma_request_chan(dev, "sata-dma");
	if (IS_ERR(hsdevp->chan)) {
		dev_err(dev, "failed to allocate dma channel: %ld\n",
			PTR_ERR(hsdevp->chan));
		return PTR_ERR(hsdevp->chan);
	}

	return 0;
}