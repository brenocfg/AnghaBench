#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_11__ {scalar_t__ of_node; scalar_t__ coherent_dma_mask; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {int dummy; } ;
struct TYPE_12__ {int src_addr_widths; int dst_addr_widths; int directions; TYPE_1__* dev; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  copy_align; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct mmp_pdma_device {int dma_channels; TYPE_3__ device; TYPE_1__* dev; int /*<<< orphan*/ * phy; int /*<<< orphan*/  base; int /*<<< orphan*/  phy_lock; } ;
struct mmp_dma_platdata {int dma_channels; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAENGINE_ALIGN_8_BYTES ; 
 scalar_t__ DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_DESCRIPTOR ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct mmp_dma_platdata* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/ * devm_kcalloc (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 struct mmp_pdma_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mmp_pdma_device*) ; 
 int dma_async_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mmp_pdma_alloc_chan_resources ; 
 int mmp_pdma_chan_init (struct mmp_pdma_device*,int,int) ; 
 int /*<<< orphan*/  mmp_pdma_config ; 
 int /*<<< orphan*/  mmp_pdma_dma_xlate ; 
 int /*<<< orphan*/  mmp_pdma_dt_ids ; 
 int /*<<< orphan*/  mmp_pdma_free_chan_resources ; 
 int /*<<< orphan*/  mmp_pdma_int_handler ; 
 int /*<<< orphan*/  mmp_pdma_issue_pending ; 
 int /*<<< orphan*/  mmp_pdma_prep_dma_cyclic ; 
 int /*<<< orphan*/  mmp_pdma_prep_memcpy ; 
 int /*<<< orphan*/  mmp_pdma_prep_slave_sg ; 
 int /*<<< orphan*/  mmp_pdma_terminate_all ; 
 int /*<<< orphan*/  mmp_pdma_tx_status ; 
 int of_dma_controller_register (scalar_t__,int /*<<< orphan*/ ,struct mmp_pdma_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_property_read_u32 (scalar_t__,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmp_pdma_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmp_pdma_probe(struct platform_device *op)
{
	struct mmp_pdma_device *pdev;
	const struct of_device_id *of_id;
	struct mmp_dma_platdata *pdata = dev_get_platdata(&op->dev);
	struct resource *iores;
	int i, ret, irq = 0;
	int dma_channels = 0, irq_num = 0;
	const enum dma_slave_buswidth widths =
		DMA_SLAVE_BUSWIDTH_1_BYTE   | DMA_SLAVE_BUSWIDTH_2_BYTES |
		DMA_SLAVE_BUSWIDTH_4_BYTES;

	pdev = devm_kzalloc(&op->dev, sizeof(*pdev), GFP_KERNEL);
	if (!pdev)
		return -ENOMEM;

	pdev->dev = &op->dev;

	spin_lock_init(&pdev->phy_lock);

	iores = platform_get_resource(op, IORESOURCE_MEM, 0);
	pdev->base = devm_ioremap_resource(pdev->dev, iores);
	if (IS_ERR(pdev->base))
		return PTR_ERR(pdev->base);

	of_id = of_match_device(mmp_pdma_dt_ids, pdev->dev);
	if (of_id)
		of_property_read_u32(pdev->dev->of_node, "#dma-channels",
				     &dma_channels);
	else if (pdata && pdata->dma_channels)
		dma_channels = pdata->dma_channels;
	else
		dma_channels = 32;	/* default 32 channel */
	pdev->dma_channels = dma_channels;

	for (i = 0; i < dma_channels; i++) {
		if (platform_get_irq(op, i) > 0)
			irq_num++;
	}

	pdev->phy = devm_kcalloc(pdev->dev, dma_channels, sizeof(*pdev->phy),
				 GFP_KERNEL);
	if (pdev->phy == NULL)
		return -ENOMEM;

	INIT_LIST_HEAD(&pdev->device.channels);

	if (irq_num != dma_channels) {
		/* all chan share one irq, demux inside */
		irq = platform_get_irq(op, 0);
		ret = devm_request_irq(pdev->dev, irq, mmp_pdma_int_handler,
				       IRQF_SHARED, "pdma", pdev);
		if (ret)
			return ret;
	}

	for (i = 0; i < dma_channels; i++) {
		irq = (irq_num != dma_channels) ? 0 : platform_get_irq(op, i);
		ret = mmp_pdma_chan_init(pdev, i, irq);
		if (ret)
			return ret;
	}

	dma_cap_set(DMA_SLAVE, pdev->device.cap_mask);
	dma_cap_set(DMA_MEMCPY, pdev->device.cap_mask);
	dma_cap_set(DMA_CYCLIC, pdev->device.cap_mask);
	dma_cap_set(DMA_PRIVATE, pdev->device.cap_mask);
	pdev->device.dev = &op->dev;
	pdev->device.device_alloc_chan_resources = mmp_pdma_alloc_chan_resources;
	pdev->device.device_free_chan_resources = mmp_pdma_free_chan_resources;
	pdev->device.device_tx_status = mmp_pdma_tx_status;
	pdev->device.device_prep_dma_memcpy = mmp_pdma_prep_memcpy;
	pdev->device.device_prep_slave_sg = mmp_pdma_prep_slave_sg;
	pdev->device.device_prep_dma_cyclic = mmp_pdma_prep_dma_cyclic;
	pdev->device.device_issue_pending = mmp_pdma_issue_pending;
	pdev->device.device_config = mmp_pdma_config;
	pdev->device.device_terminate_all = mmp_pdma_terminate_all;
	pdev->device.copy_align = DMAENGINE_ALIGN_8_BYTES;
	pdev->device.src_addr_widths = widths;
	pdev->device.dst_addr_widths = widths;
	pdev->device.directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	pdev->device.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;

	if (pdev->dev->coherent_dma_mask)
		dma_set_mask(pdev->dev, pdev->dev->coherent_dma_mask);
	else
		dma_set_mask(pdev->dev, DMA_BIT_MASK(64));

	ret = dma_async_device_register(&pdev->device);
	if (ret) {
		dev_err(pdev->device.dev, "unable to register\n");
		return ret;
	}

	if (op->dev.of_node) {
		/* Device-tree DMA controller registration */
		ret = of_dma_controller_register(op->dev.of_node,
						 mmp_pdma_dma_xlate, pdev);
		if (ret < 0) {
			dev_err(&op->dev, "of_dma_controller_register failed\n");
			return ret;
		}
	}

	platform_set_drvdata(op, pdev);
	dev_info(pdev->device.dev, "initialized %d channels\n", dma_channels);
	return 0;
}