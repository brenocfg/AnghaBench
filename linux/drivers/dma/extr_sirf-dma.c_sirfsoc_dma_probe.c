#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u32 ;
struct sirfsoc_dmadata {int /*<<< orphan*/  type; int /*<<< orphan*/  exec; } ;
struct TYPE_6__ {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct sirfsoc_dma_chan {TYPE_3__ chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  completed; int /*<<< orphan*/  active; int /*<<< orphan*/  queued; int /*<<< orphan*/  prepared; int /*<<< orphan*/  free; } ;
struct dma_device {int directions; int /*<<< orphan*/  channels; int /*<<< orphan*/  cap_mask; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_interleaved_dma; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; struct device* dev; } ;
struct sirfsoc_dma {int /*<<< orphan*/  irq; int /*<<< orphan*/  tasklet; struct sirfsoc_dma_chan* channels; struct dma_device dma; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; int /*<<< orphan*/  type; int /*<<< orphan*/  exec_desc; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {TYPE_1__* driver; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_INTERLEAVE ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* SIRFSOC_DMA_BUSWIDTHS ; 
 int SIRFSOC_DMA_CHANNELS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sirfsoc_dma*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sirfsoc_dma* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_3__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sirfsoc_dma*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int of_dma_controller_register (struct device_node*,int /*<<< orphan*/ ,struct sirfsoc_dma*) ; 
 int /*<<< orphan*/  of_dma_sirfsoc_xlate ; 
 TYPE_2__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sirfsoc_dma*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sirfsoc_dma_alloc_chan_resources ; 
 int /*<<< orphan*/  sirfsoc_dma_free_chan_resources ; 
 int /*<<< orphan*/  sirfsoc_dma_irq ; 
 int /*<<< orphan*/  sirfsoc_dma_issue_pending ; 
 int /*<<< orphan*/  sirfsoc_dma_pause_chan ; 
 int /*<<< orphan*/  sirfsoc_dma_prep_cyclic ; 
 int /*<<< orphan*/  sirfsoc_dma_prep_interleaved ; 
 int /*<<< orphan*/  sirfsoc_dma_resume_chan ; 
 int /*<<< orphan*/  sirfsoc_dma_slave_config ; 
 int /*<<< orphan*/  sirfsoc_dma_tasklet ; 
 int /*<<< orphan*/  sirfsoc_dma_terminate_all ; 
 int /*<<< orphan*/  sirfsoc_dma_tx_status ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sirfsoc_dma_probe(struct platform_device *op)
{
	struct device_node *dn = op->dev.of_node;
	struct device *dev = &op->dev;
	struct dma_device *dma;
	struct sirfsoc_dma *sdma;
	struct sirfsoc_dma_chan *schan;
	struct sirfsoc_dmadata *data;
	struct resource res;
	ulong regs_start, regs_size;
	u32 id;
	int ret, i;

	sdma = devm_kzalloc(dev, sizeof(*sdma), GFP_KERNEL);
	if (!sdma)
		return -ENOMEM;

	data = (struct sirfsoc_dmadata *)
		(of_match_device(op->dev.driver->of_match_table,
				 &op->dev)->data);
	sdma->exec_desc = data->exec;
	sdma->type = data->type;

	if (of_property_read_u32(dn, "cell-index", &id)) {
		dev_err(dev, "Fail to get DMAC index\n");
		return -ENODEV;
	}

	sdma->irq = irq_of_parse_and_map(dn, 0);
	if (!sdma->irq) {
		dev_err(dev, "Error mapping IRQ!\n");
		return -EINVAL;
	}

	sdma->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(sdma->clk)) {
		dev_err(dev, "failed to get a clock.\n");
		return PTR_ERR(sdma->clk);
	}

	ret = of_address_to_resource(dn, 0, &res);
	if (ret) {
		dev_err(dev, "Error parsing memory region!\n");
		goto irq_dispose;
	}

	regs_start = res.start;
	regs_size = resource_size(&res);

	sdma->base = devm_ioremap(dev, regs_start, regs_size);
	if (!sdma->base) {
		dev_err(dev, "Error mapping memory region!\n");
		ret = -ENOMEM;
		goto irq_dispose;
	}

	ret = request_irq(sdma->irq, &sirfsoc_dma_irq, 0, DRV_NAME, sdma);
	if (ret) {
		dev_err(dev, "Error requesting IRQ!\n");
		ret = -EINVAL;
		goto irq_dispose;
	}

	dma = &sdma->dma;
	dma->dev = dev;

	dma->device_alloc_chan_resources = sirfsoc_dma_alloc_chan_resources;
	dma->device_free_chan_resources = sirfsoc_dma_free_chan_resources;
	dma->device_issue_pending = sirfsoc_dma_issue_pending;
	dma->device_config = sirfsoc_dma_slave_config;
	dma->device_pause = sirfsoc_dma_pause_chan;
	dma->device_resume = sirfsoc_dma_resume_chan;
	dma->device_terminate_all = sirfsoc_dma_terminate_all;
	dma->device_tx_status = sirfsoc_dma_tx_status;
	dma->device_prep_interleaved_dma = sirfsoc_dma_prep_interleaved;
	dma->device_prep_dma_cyclic = sirfsoc_dma_prep_cyclic;
	dma->src_addr_widths = SIRFSOC_DMA_BUSWIDTHS;
	dma->dst_addr_widths = SIRFSOC_DMA_BUSWIDTHS;
	dma->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	INIT_LIST_HEAD(&dma->channels);
	dma_cap_set(DMA_SLAVE, dma->cap_mask);
	dma_cap_set(DMA_CYCLIC, dma->cap_mask);
	dma_cap_set(DMA_INTERLEAVE, dma->cap_mask);
	dma_cap_set(DMA_PRIVATE, dma->cap_mask);

	for (i = 0; i < SIRFSOC_DMA_CHANNELS; i++) {
		schan = &sdma->channels[i];

		schan->chan.device = dma;
		dma_cookie_init(&schan->chan);

		INIT_LIST_HEAD(&schan->free);
		INIT_LIST_HEAD(&schan->prepared);
		INIT_LIST_HEAD(&schan->queued);
		INIT_LIST_HEAD(&schan->active);
		INIT_LIST_HEAD(&schan->completed);

		spin_lock_init(&schan->lock);
		list_add_tail(&schan->chan.device_node, &dma->channels);
	}

	tasklet_init(&sdma->tasklet, sirfsoc_dma_tasklet, (unsigned long)sdma);

	/* Register DMA engine */
	dev_set_drvdata(dev, sdma);

	ret = dma_async_device_register(dma);
	if (ret)
		goto free_irq;

	/* Device-tree DMA controller registration */
	ret = of_dma_controller_register(dn, of_dma_sirfsoc_xlate, sdma);
	if (ret) {
		dev_err(dev, "failed to register DMA controller\n");
		goto unreg_dma_dev;
	}

	pm_runtime_enable(&op->dev);
	dev_info(dev, "initialized SIRFSOC DMAC driver\n");

	return 0;

unreg_dma_dev:
	dma_async_device_unregister(dma);
free_irq:
	free_irq(sdma->irq, sdma);
irq_dispose:
	irq_dispose_mapping(sdma->irq);
	return ret;
}