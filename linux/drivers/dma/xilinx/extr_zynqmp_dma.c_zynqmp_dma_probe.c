#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct dma_device {void* src_addr_widths; void* dst_addr_widths; TYPE_1__* dev; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct zynqmp_dma_device {TYPE_1__* dev; TYPE_3__* chan; struct dma_device common; void* clk_apb; void* clk_main; } ;
struct TYPE_17__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_18__ {int bus_width; } ;

/* Variables and functions */
 void* BIT (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ZDMA_PM_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct zynqmp_dma_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_status ; 
 int /*<<< orphan*/  dma_set_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zynqmp_dma_device*) ; 
 int /*<<< orphan*/  of_zynqmp_dma_xlate ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zynqmp_dma_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  zynqmp_dma_alloc_chan_resources ; 
 int zynqmp_dma_chan_probe (struct zynqmp_dma_device*,struct platform_device*) ; 
 int /*<<< orphan*/  zynqmp_dma_chan_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  zynqmp_dma_device_config ; 
 int /*<<< orphan*/  zynqmp_dma_device_terminate_all ; 
 int /*<<< orphan*/  zynqmp_dma_free_chan_resources ; 
 int /*<<< orphan*/  zynqmp_dma_issue_pending ; 
 int /*<<< orphan*/  zynqmp_dma_prep_memcpy ; 
 int zynqmp_dma_runtime_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  zynqmp_dma_runtime_suspend (TYPE_1__*) ; 

__attribute__((used)) static int zynqmp_dma_probe(struct platform_device *pdev)
{
	struct zynqmp_dma_device *zdev;
	struct dma_device *p;
	int ret;

	zdev = devm_kzalloc(&pdev->dev, sizeof(*zdev), GFP_KERNEL);
	if (!zdev)
		return -ENOMEM;

	zdev->dev = &pdev->dev;
	INIT_LIST_HEAD(&zdev->common.channels);

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(44));
	dma_cap_set(DMA_MEMCPY, zdev->common.cap_mask);

	p = &zdev->common;
	p->device_prep_dma_memcpy = zynqmp_dma_prep_memcpy;
	p->device_terminate_all = zynqmp_dma_device_terminate_all;
	p->device_issue_pending = zynqmp_dma_issue_pending;
	p->device_alloc_chan_resources = zynqmp_dma_alloc_chan_resources;
	p->device_free_chan_resources = zynqmp_dma_free_chan_resources;
	p->device_tx_status = dma_cookie_status;
	p->device_config = zynqmp_dma_device_config;
	p->dev = &pdev->dev;

	zdev->clk_main = devm_clk_get(&pdev->dev, "clk_main");
	if (IS_ERR(zdev->clk_main)) {
		dev_err(&pdev->dev, "main clock not found.\n");
		return PTR_ERR(zdev->clk_main);
	}

	zdev->clk_apb = devm_clk_get(&pdev->dev, "clk_apb");
	if (IS_ERR(zdev->clk_apb)) {
		dev_err(&pdev->dev, "apb clock not found.\n");
		return PTR_ERR(zdev->clk_apb);
	}

	platform_set_drvdata(pdev, zdev);
	pm_runtime_set_autosuspend_delay(zdev->dev, ZDMA_PM_TIMEOUT);
	pm_runtime_use_autosuspend(zdev->dev);
	pm_runtime_enable(zdev->dev);
	pm_runtime_get_sync(zdev->dev);
	if (!pm_runtime_enabled(zdev->dev)) {
		ret = zynqmp_dma_runtime_resume(zdev->dev);
		if (ret)
			return ret;
	}

	ret = zynqmp_dma_chan_probe(zdev, pdev);
	if (ret) {
		dev_err(&pdev->dev, "Probing channel failed\n");
		goto err_disable_pm;
	}

	p->dst_addr_widths = BIT(zdev->chan->bus_width / 8);
	p->src_addr_widths = BIT(zdev->chan->bus_width / 8);

	dma_async_device_register(&zdev->common);

	ret = of_dma_controller_register(pdev->dev.of_node,
					 of_zynqmp_dma_xlate, zdev);
	if (ret) {
		dev_err(&pdev->dev, "Unable to register DMA to DT\n");
		dma_async_device_unregister(&zdev->common);
		goto free_chan_resources;
	}

	pm_runtime_mark_last_busy(zdev->dev);
	pm_runtime_put_sync_autosuspend(zdev->dev);

	dev_info(&pdev->dev, "ZynqMP DMA driver Probe success\n");

	return 0;

free_chan_resources:
	zynqmp_dma_chan_remove(zdev->chan);
err_disable_pm:
	if (!pm_runtime_enabled(zdev->dev))
		zynqmp_dma_runtime_suspend(zdev->dev);
	pm_runtime_disable(zdev->dev);
	return ret;
}