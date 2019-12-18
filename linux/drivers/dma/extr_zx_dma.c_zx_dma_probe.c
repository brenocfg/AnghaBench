#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct zx_dma_phy {int idx; scalar_t__ base; } ;
struct TYPE_14__ {int directions; int /*<<< orphan*/  residue_granularity; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  copy_align; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; TYPE_3__* dev; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct zx_dma_dev {int dma_channels; int dma_requests; scalar_t__ clk; TYPE_2__ slave; int /*<<< orphan*/  chan_pending; int /*<<< orphan*/  lock; struct zx_dma_chan* chans; scalar_t__ base; struct zx_dma_phy* phy; int /*<<< orphan*/  pool; int /*<<< orphan*/  irq; } ;
struct TYPE_13__ {int /*<<< orphan*/  desc_free; } ;
struct zx_dma_chan {TYPE_1__ vc; int /*<<< orphan*/  node; int /*<<< orphan*/  status; } ;
struct resource {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_ALIGN ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_IN_PROGRESS ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_SEGMENT ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  LLI_BLOCK_SIZE ; 
 int PTR_ERR (scalar_t__) ; 
 void* ZX_DMA_BUSWIDTHS ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*) ; 
 scalar_t__ devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 void* devm_kcalloc (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 struct zx_dma_dev* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zx_dma_dev*) ; 
 int dma_async_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_pool_create (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int of_dma_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zx_dma_dev*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zx_dma_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zx_dma_config ; 
 int /*<<< orphan*/  zx_dma_free_chan_resources ; 
 int /*<<< orphan*/  zx_dma_free_desc ; 
 int /*<<< orphan*/  zx_dma_init_state (struct zx_dma_dev*) ; 
 int /*<<< orphan*/  zx_dma_int_handler ; 
 int /*<<< orphan*/  zx_dma_issue_pending ; 
 int /*<<< orphan*/  zx_dma_prep_dma_cyclic ; 
 int /*<<< orphan*/  zx_dma_prep_memcpy ; 
 int /*<<< orphan*/  zx_dma_prep_slave_sg ; 
 int /*<<< orphan*/  zx_dma_terminate_all ; 
 int /*<<< orphan*/  zx_dma_transfer_pause ; 
 int /*<<< orphan*/  zx_dma_transfer_resume ; 
 int /*<<< orphan*/  zx_dma_tx_status ; 
 int /*<<< orphan*/  zx_of_dma_simple_xlate ; 

__attribute__((used)) static int zx_dma_probe(struct platform_device *op)
{
	struct zx_dma_dev *d;
	struct resource *iores;
	int i, ret = 0;

	iores = platform_get_resource(op, IORESOURCE_MEM, 0);
	if (!iores)
		return -EINVAL;

	d = devm_kzalloc(&op->dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	d->base = devm_ioremap_resource(&op->dev, iores);
	if (IS_ERR(d->base))
		return PTR_ERR(d->base);

	of_property_read_u32((&op->dev)->of_node,
			     "dma-channels", &d->dma_channels);
	of_property_read_u32((&op->dev)->of_node,
			     "dma-requests", &d->dma_requests);
	if (!d->dma_requests || !d->dma_channels)
		return -EINVAL;

	d->clk = devm_clk_get(&op->dev, NULL);
	if (IS_ERR(d->clk)) {
		dev_err(&op->dev, "no dma clk\n");
		return PTR_ERR(d->clk);
	}

	d->irq = platform_get_irq(op, 0);
	ret = devm_request_irq(&op->dev, d->irq, zx_dma_int_handler,
			       0, DRIVER_NAME, d);
	if (ret)
		return ret;

	/* A DMA memory pool for LLIs, align on 32-byte boundary */
	d->pool = dmam_pool_create(DRIVER_NAME, &op->dev,
			LLI_BLOCK_SIZE, 32, 0);
	if (!d->pool)
		return -ENOMEM;

	/* init phy channel */
	d->phy = devm_kcalloc(&op->dev,
		d->dma_channels, sizeof(struct zx_dma_phy), GFP_KERNEL);
	if (!d->phy)
		return -ENOMEM;

	for (i = 0; i < d->dma_channels; i++) {
		struct zx_dma_phy *p = &d->phy[i];

		p->idx = i;
		p->base = d->base + i * 0x40;
	}

	INIT_LIST_HEAD(&d->slave.channels);
	dma_cap_set(DMA_SLAVE, d->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, d->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, d->slave.cap_mask);
	dma_cap_set(DMA_PRIVATE, d->slave.cap_mask);
	d->slave.dev = &op->dev;
	d->slave.device_free_chan_resources = zx_dma_free_chan_resources;
	d->slave.device_tx_status = zx_dma_tx_status;
	d->slave.device_prep_dma_memcpy = zx_dma_prep_memcpy;
	d->slave.device_prep_slave_sg = zx_dma_prep_slave_sg;
	d->slave.device_prep_dma_cyclic = zx_dma_prep_dma_cyclic;
	d->slave.device_issue_pending = zx_dma_issue_pending;
	d->slave.device_config = zx_dma_config;
	d->slave.device_terminate_all = zx_dma_terminate_all;
	d->slave.device_pause = zx_dma_transfer_pause;
	d->slave.device_resume = zx_dma_transfer_resume;
	d->slave.copy_align = DMA_ALIGN;
	d->slave.src_addr_widths = ZX_DMA_BUSWIDTHS;
	d->slave.dst_addr_widths = ZX_DMA_BUSWIDTHS;
	d->slave.directions = BIT(DMA_MEM_TO_MEM) | BIT(DMA_MEM_TO_DEV)
			| BIT(DMA_DEV_TO_MEM);
	d->slave.residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;

	/* init virtual channel */
	d->chans = devm_kcalloc(&op->dev,
		d->dma_requests, sizeof(struct zx_dma_chan), GFP_KERNEL);
	if (!d->chans)
		return -ENOMEM;

	for (i = 0; i < d->dma_requests; i++) {
		struct zx_dma_chan *c = &d->chans[i];

		c->status = DMA_IN_PROGRESS;
		INIT_LIST_HEAD(&c->node);
		c->vc.desc_free = zx_dma_free_desc;
		vchan_init(&c->vc, &d->slave);
	}

	/* Enable clock before accessing registers */
	ret = clk_prepare_enable(d->clk);
	if (ret < 0) {
		dev_err(&op->dev, "clk_prepare_enable failed: %d\n", ret);
		goto zx_dma_out;
	}

	zx_dma_init_state(d);

	spin_lock_init(&d->lock);
	INIT_LIST_HEAD(&d->chan_pending);
	platform_set_drvdata(op, d);

	ret = dma_async_device_register(&d->slave);
	if (ret)
		goto clk_dis;

	ret = of_dma_controller_register((&op->dev)->of_node,
					 zx_of_dma_simple_xlate, d);
	if (ret)
		goto of_dma_register_fail;

	dev_info(&op->dev, "initialized\n");
	return 0;

of_dma_register_fail:
	dma_async_device_unregister(&d->slave);
clk_dis:
	clk_disable_unprepare(d->clk);
zx_dma_out:
	return ret;
}