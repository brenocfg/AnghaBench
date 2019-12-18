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
struct dma_device {int directions; int /*<<< orphan*/  channels; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_synchronize; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  residue_granularity; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  cap_mask; struct device* dev; } ;
struct uniphier_mdmac_device {int /*<<< orphan*/  clk; struct dma_device ddev; int /*<<< orphan*/  reg_base; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_SEGMENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* UNIPHIER_MDMAC_SLAVE_BUSWIDTHS ; 
 int /*<<< orphan*/  channels ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct uniphier_mdmac_device* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_mask (struct device*,int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_device*) ; 
 int /*<<< orphan*/  of_dma_xlate_by_chan_id ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_mdmac_device*) ; 
 int /*<<< orphan*/  struct_size (struct uniphier_mdmac_device*,int /*<<< orphan*/ ,int) ; 
 int uniphier_mdmac_chan_init (struct platform_device*,struct uniphier_mdmac_device*,int) ; 
 int /*<<< orphan*/  uniphier_mdmac_free_chan_resources ; 
 int /*<<< orphan*/  uniphier_mdmac_issue_pending ; 
 int /*<<< orphan*/  uniphier_mdmac_prep_slave_sg ; 
 int /*<<< orphan*/  uniphier_mdmac_synchronize ; 
 int /*<<< orphan*/  uniphier_mdmac_terminate_all ; 
 int /*<<< orphan*/  uniphier_mdmac_tx_status ; 

__attribute__((used)) static int uniphier_mdmac_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uniphier_mdmac_device *mdev;
	struct dma_device *ddev;
	struct resource *res;
	int nr_chans, ret, i;

	nr_chans = platform_irq_count(pdev);
	if (nr_chans < 0)
		return nr_chans;

	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	mdev = devm_kzalloc(dev, struct_size(mdev, channels, nr_chans),
			    GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mdev->reg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(mdev->reg_base))
		return PTR_ERR(mdev->reg_base);

	mdev->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(mdev->clk)) {
		dev_err(dev, "failed to get clock\n");
		return PTR_ERR(mdev->clk);
	}

	ret = clk_prepare_enable(mdev->clk);
	if (ret)
		return ret;

	ddev = &mdev->ddev;
	ddev->dev = dev;
	dma_cap_set(DMA_PRIVATE, ddev->cap_mask);
	ddev->src_addr_widths = UNIPHIER_MDMAC_SLAVE_BUSWIDTHS;
	ddev->dst_addr_widths = UNIPHIER_MDMAC_SLAVE_BUSWIDTHS;
	ddev->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	ddev->residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	ddev->device_free_chan_resources = uniphier_mdmac_free_chan_resources;
	ddev->device_prep_slave_sg = uniphier_mdmac_prep_slave_sg;
	ddev->device_terminate_all = uniphier_mdmac_terminate_all;
	ddev->device_synchronize = uniphier_mdmac_synchronize;
	ddev->device_tx_status = uniphier_mdmac_tx_status;
	ddev->device_issue_pending = uniphier_mdmac_issue_pending;
	INIT_LIST_HEAD(&ddev->channels);

	for (i = 0; i < nr_chans; i++) {
		ret = uniphier_mdmac_chan_init(pdev, mdev, i);
		if (ret)
			goto disable_clk;
	}

	ret = dma_async_device_register(ddev);
	if (ret)
		goto disable_clk;

	ret = of_dma_controller_register(dev->of_node, of_dma_xlate_by_chan_id,
					 ddev);
	if (ret)
		goto unregister_dmac;

	platform_set_drvdata(pdev, mdev);

	return 0;

unregister_dmac:
	dma_async_device_unregister(ddev);
disable_clk:
	clk_disable_unprepare(mdev->clk);

	return ret;
}