#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct dma_device {int src_addr_widths; int dst_addr_widths; int directions; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  residue_granularity; TYPE_1__* dev; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct usb_dmac {unsigned int n_channels; struct dma_device engine; int /*<<< orphan*/ * channels; int /*<<< orphan*/  iomem; TYPE_1__* dev; } ;
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_BURST ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int USB_DMAC_SLAVE_BUSWIDTH ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/ * devm_kcalloc (TYPE_1__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct usb_dmac* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usb_dmac*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_dmac_alloc_chan_resources ; 
 int usb_dmac_chan_probe (struct usb_dmac*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  usb_dmac_chan_terminate_all ; 
 int /*<<< orphan*/  usb_dmac_free_chan_resources ; 
 int usb_dmac_init (struct usb_dmac*) ; 
 int /*<<< orphan*/  usb_dmac_issue_pending ; 
 int /*<<< orphan*/  usb_dmac_of_xlate ; 
 int usb_dmac_parse_of (TYPE_1__*,struct usb_dmac*) ; 
 int /*<<< orphan*/  usb_dmac_prep_slave_sg ; 
 int /*<<< orphan*/  usb_dmac_tx_status ; 

__attribute__((used)) static int usb_dmac_probe(struct platform_device *pdev)
{
	const enum dma_slave_buswidth widths = USB_DMAC_SLAVE_BUSWIDTH;
	struct dma_device *engine;
	struct usb_dmac *dmac;
	struct resource *mem;
	unsigned int i;
	int ret;

	dmac = devm_kzalloc(&pdev->dev, sizeof(*dmac), GFP_KERNEL);
	if (!dmac)
		return -ENOMEM;

	dmac->dev = &pdev->dev;
	platform_set_drvdata(pdev, dmac);

	ret = usb_dmac_parse_of(&pdev->dev, dmac);
	if (ret < 0)
		return ret;

	dmac->channels = devm_kcalloc(&pdev->dev, dmac->n_channels,
				      sizeof(*dmac->channels), GFP_KERNEL);
	if (!dmac->channels)
		return -ENOMEM;

	/* Request resources. */
	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dmac->iomem = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dmac->iomem))
		return PTR_ERR(dmac->iomem);

	/* Enable runtime PM and initialize the device. */
	pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "runtime PM get sync failed (%d)\n", ret);
		goto error_pm;
	}

	ret = usb_dmac_init(dmac);

	if (ret) {
		dev_err(&pdev->dev, "failed to reset device\n");
		goto error;
	}

	/* Initialize the channels. */
	INIT_LIST_HEAD(&dmac->engine.channels);

	for (i = 0; i < dmac->n_channels; ++i) {
		ret = usb_dmac_chan_probe(dmac, &dmac->channels[i], i);
		if (ret < 0)
			goto error;
	}

	/* Register the DMAC as a DMA provider for DT. */
	ret = of_dma_controller_register(pdev->dev.of_node, usb_dmac_of_xlate,
					 NULL);
	if (ret < 0)
		goto error;

	/*
	 * Register the DMA engine device.
	 *
	 * Default transfer size of 32 bytes requires 32-byte alignment.
	 */
	engine = &dmac->engine;
	dma_cap_set(DMA_SLAVE, engine->cap_mask);

	engine->dev = &pdev->dev;

	engine->src_addr_widths = widths;
	engine->dst_addr_widths = widths;
	engine->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	engine->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	engine->device_alloc_chan_resources = usb_dmac_alloc_chan_resources;
	engine->device_free_chan_resources = usb_dmac_free_chan_resources;
	engine->device_prep_slave_sg = usb_dmac_prep_slave_sg;
	engine->device_terminate_all = usb_dmac_chan_terminate_all;
	engine->device_tx_status = usb_dmac_tx_status;
	engine->device_issue_pending = usb_dmac_issue_pending;

	ret = dma_async_device_register(engine);
	if (ret < 0)
		goto error;

	pm_runtime_put(&pdev->dev);
	return 0;

error:
	of_dma_controller_free(pdev->dev.of_node);
	pm_runtime_put(&pdev->dev);
error_pm:
	pm_runtime_disable(&pdev->dev);
	return ret;
}