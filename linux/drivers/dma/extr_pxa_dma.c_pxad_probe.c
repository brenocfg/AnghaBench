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
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_10__ {int mapcnt; int /*<<< orphan*/  fn; struct dma_slave_map const* map; } ;
struct TYPE_11__ {int src_addr_widths; int dst_addr_widths; int directions; int descriptor_reuse; TYPE_3__* dev; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  copy_align; TYPE_1__ filter; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  cap_mask; } ;
struct pxad_device {TYPE_2__ slave; int /*<<< orphan*/  base; int /*<<< orphan*/  phy_lock; } ;
struct TYPE_12__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {int dummy; } ;
struct mmp_dma_platdata {int dma_channels; int nb_requestors; int slave_map_cnt; struct dma_slave_map* slave_map; } ;
struct dma_slave_map {int dummy; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDMA_ALIGNMENT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct mmp_dma_platdata* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct pxad_device* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (scalar_t__,int /*<<< orphan*/ ,struct pxad_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int of_property_read_u32 (scalar_t__,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxad_device*) ; 
 int /*<<< orphan*/  pxad_dma_xlate ; 
 int /*<<< orphan*/  pxad_dt_ids ; 
 int /*<<< orphan*/  pxad_filter_fn ; 
 int /*<<< orphan*/  pxad_init_debugfs (struct pxad_device*) ; 
 int pxad_init_dmadev (struct platform_device*,struct pxad_device*,int,int) ; 
 int /*<<< orphan*/  pxad_prep_dma_cyclic ; 
 int /*<<< orphan*/  pxad_prep_memcpy ; 
 int /*<<< orphan*/  pxad_prep_slave_sg ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxad_probe(struct platform_device *op)
{
	struct pxad_device *pdev;
	const struct of_device_id *of_id;
	const struct dma_slave_map *slave_map = NULL;
	struct mmp_dma_platdata *pdata = dev_get_platdata(&op->dev);
	struct resource *iores;
	int ret, dma_channels = 0, nb_requestors = 0, slave_map_cnt = 0;
	const enum dma_slave_buswidth widths =
		DMA_SLAVE_BUSWIDTH_1_BYTE   | DMA_SLAVE_BUSWIDTH_2_BYTES |
		DMA_SLAVE_BUSWIDTH_4_BYTES;

	pdev = devm_kzalloc(&op->dev, sizeof(*pdev), GFP_KERNEL);
	if (!pdev)
		return -ENOMEM;

	spin_lock_init(&pdev->phy_lock);

	iores = platform_get_resource(op, IORESOURCE_MEM, 0);
	pdev->base = devm_ioremap_resource(&op->dev, iores);
	if (IS_ERR(pdev->base))
		return PTR_ERR(pdev->base);

	of_id = of_match_device(pxad_dt_ids, &op->dev);
	if (of_id) {
		of_property_read_u32(op->dev.of_node, "#dma-channels",
				     &dma_channels);
		ret = of_property_read_u32(op->dev.of_node, "#dma-requests",
					   &nb_requestors);
		if (ret) {
			dev_warn(pdev->slave.dev,
				 "#dma-requests set to default 32 as missing in OF: %d",
				 ret);
			nb_requestors = 32;
		}
	} else if (pdata && pdata->dma_channels) {
		dma_channels = pdata->dma_channels;
		nb_requestors = pdata->nb_requestors;
		slave_map = pdata->slave_map;
		slave_map_cnt = pdata->slave_map_cnt;
	} else {
		dma_channels = 32;	/* default 32 channel */
	}

	dma_cap_set(DMA_SLAVE, pdev->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, pdev->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, pdev->slave.cap_mask);
	dma_cap_set(DMA_PRIVATE, pdev->slave.cap_mask);
	pdev->slave.device_prep_dma_memcpy = pxad_prep_memcpy;
	pdev->slave.device_prep_slave_sg = pxad_prep_slave_sg;
	pdev->slave.device_prep_dma_cyclic = pxad_prep_dma_cyclic;
	pdev->slave.filter.map = slave_map;
	pdev->slave.filter.mapcnt = slave_map_cnt;
	pdev->slave.filter.fn = pxad_filter_fn;

	pdev->slave.copy_align = PDMA_ALIGNMENT;
	pdev->slave.src_addr_widths = widths;
	pdev->slave.dst_addr_widths = widths;
	pdev->slave.directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	pdev->slave.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	pdev->slave.descriptor_reuse = true;

	pdev->slave.dev = &op->dev;
	ret = pxad_init_dmadev(op, pdev, dma_channels, nb_requestors);
	if (ret) {
		dev_err(pdev->slave.dev, "unable to register\n");
		return ret;
	}

	if (op->dev.of_node) {
		/* Device-tree DMA controller registration */
		ret = of_dma_controller_register(op->dev.of_node,
						 pxad_dma_xlate, pdev);
		if (ret < 0) {
			dev_err(pdev->slave.dev,
				"of_dma_controller_register failed\n");
			return ret;
		}
	}

	platform_set_drvdata(op, pdev);
	pxad_init_debugfs(pdev);
	dev_info(pdev->slave.dev, "initialized %d channels on %d requestors\n",
		 dma_channels, nb_requestors);
	return 0;
}