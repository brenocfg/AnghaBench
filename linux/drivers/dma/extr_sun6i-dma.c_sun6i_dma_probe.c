#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  desc_free; } ;
struct sun6i_vchan {TYPE_1__ vc; int /*<<< orphan*/  node; } ;
struct sun6i_pchan {int idx; void* base; } ;
struct sun6i_dma_lli {int dummy; } ;
struct TYPE_19__ {int directions; TYPE_4__* dev; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  dst_addr_widths; int /*<<< orphan*/  src_addr_widths; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_config; int /*<<< orphan*/  copy_align; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  channels; int /*<<< orphan*/  cap_mask; } ;
struct sun6i_dma_dev {scalar_t__ irq; int num_pchans; int num_vchans; int max_request; void* rstc; void* clk; void* clk_mbus; TYPE_2__ slave; TYPE_3__* cfg; struct sun6i_vchan* vchans; void* base; struct sun6i_pchan* pchans; int /*<<< orphan*/  task; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  pool; } ;
struct resource {int dummy; } ;
struct TYPE_21__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_20__ {int nr_max_channels; int nr_max_vchans; int nr_max_requests; int /*<<< orphan*/  (* clock_autogate_enable ) (struct sun6i_dma_dev*) ;scalar_t__ has_mbus_clk; int /*<<< orphan*/  dst_addr_widths; int /*<<< orphan*/  src_addr_widths; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAENGINE_ALIGN_4_BYTES ; 
 int DMA_CHAN_MAX_DRQ_A31 ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_RESIDUE_GRANULARITY_BURST ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*) ; 
 void* devm_clk_get (TYPE_4__*,char*) ; 
 void* devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 void* devm_kcalloc (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 struct sun6i_dma_dev* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sun6i_dma_dev*) ; 
 void* devm_reset_control_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int dma_async_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_pool_create (int /*<<< orphan*/ ,TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* of_device_get_match_data (TYPE_4__*) ; 
 int of_dma_controller_register (struct device_node*,int /*<<< orphan*/ ,struct sun6i_dma_dev*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  reset_control_assert (void*) ; 
 int reset_control_deassert (void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  sun6i_dma_config ; 
 int /*<<< orphan*/  sun6i_dma_free (struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  sun6i_dma_free_chan_resources ; 
 int /*<<< orphan*/  sun6i_dma_free_desc ; 
 int /*<<< orphan*/  sun6i_dma_interrupt ; 
 int /*<<< orphan*/  sun6i_dma_issue_pending ; 
 int /*<<< orphan*/  sun6i_dma_of_xlate ; 
 int /*<<< orphan*/  sun6i_dma_pause ; 
 int /*<<< orphan*/  sun6i_dma_prep_dma_cyclic ; 
 int /*<<< orphan*/  sun6i_dma_prep_dma_memcpy ; 
 int /*<<< orphan*/  sun6i_dma_prep_slave_sg ; 
 int /*<<< orphan*/  sun6i_dma_resume ; 
 int /*<<< orphan*/  sun6i_dma_tasklet ; 
 int /*<<< orphan*/  sun6i_dma_terminate_all ; 
 int /*<<< orphan*/  sun6i_dma_tx_status ; 
 int /*<<< orphan*/  sun6i_kill_tasklet (struct sun6i_dma_dev*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int sun6i_dma_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sun6i_dma_dev *sdc;
	struct resource *res;
	int ret, i;

	sdc = devm_kzalloc(&pdev->dev, sizeof(*sdc), GFP_KERNEL);
	if (!sdc)
		return -ENOMEM;

	sdc->cfg = of_device_get_match_data(&pdev->dev);
	if (!sdc->cfg)
		return -ENODEV;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sdc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sdc->base))
		return PTR_ERR(sdc->base);

	sdc->irq = platform_get_irq(pdev, 0);
	if (sdc->irq < 0)
		return sdc->irq;

	sdc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(sdc->clk)) {
		dev_err(&pdev->dev, "No clock specified\n");
		return PTR_ERR(sdc->clk);
	}

	if (sdc->cfg->has_mbus_clk) {
		sdc->clk_mbus = devm_clk_get(&pdev->dev, "mbus");
		if (IS_ERR(sdc->clk_mbus)) {
			dev_err(&pdev->dev, "No mbus clock specified\n");
			return PTR_ERR(sdc->clk_mbus);
		}
	}

	sdc->rstc = devm_reset_control_get(&pdev->dev, NULL);
	if (IS_ERR(sdc->rstc)) {
		dev_err(&pdev->dev, "No reset controller specified\n");
		return PTR_ERR(sdc->rstc);
	}

	sdc->pool = dmam_pool_create(dev_name(&pdev->dev), &pdev->dev,
				     sizeof(struct sun6i_dma_lli), 4, 0);
	if (!sdc->pool) {
		dev_err(&pdev->dev, "No memory for descriptors dma pool\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, sdc);
	INIT_LIST_HEAD(&sdc->pending);
	spin_lock_init(&sdc->lock);

	dma_cap_set(DMA_PRIVATE, sdc->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, sdc->slave.cap_mask);
	dma_cap_set(DMA_SLAVE, sdc->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, sdc->slave.cap_mask);

	INIT_LIST_HEAD(&sdc->slave.channels);
	sdc->slave.device_free_chan_resources	= sun6i_dma_free_chan_resources;
	sdc->slave.device_tx_status		= sun6i_dma_tx_status;
	sdc->slave.device_issue_pending		= sun6i_dma_issue_pending;
	sdc->slave.device_prep_slave_sg		= sun6i_dma_prep_slave_sg;
	sdc->slave.device_prep_dma_memcpy	= sun6i_dma_prep_dma_memcpy;
	sdc->slave.device_prep_dma_cyclic	= sun6i_dma_prep_dma_cyclic;
	sdc->slave.copy_align			= DMAENGINE_ALIGN_4_BYTES;
	sdc->slave.device_config		= sun6i_dma_config;
	sdc->slave.device_pause			= sun6i_dma_pause;
	sdc->slave.device_resume		= sun6i_dma_resume;
	sdc->slave.device_terminate_all		= sun6i_dma_terminate_all;
	sdc->slave.src_addr_widths		= sdc->cfg->src_addr_widths;
	sdc->slave.dst_addr_widths		= sdc->cfg->dst_addr_widths;
	sdc->slave.directions			= BIT(DMA_DEV_TO_MEM) |
						  BIT(DMA_MEM_TO_DEV);
	sdc->slave.residue_granularity		= DMA_RESIDUE_GRANULARITY_BURST;
	sdc->slave.dev = &pdev->dev;

	sdc->num_pchans = sdc->cfg->nr_max_channels;
	sdc->num_vchans = sdc->cfg->nr_max_vchans;
	sdc->max_request = sdc->cfg->nr_max_requests;

	ret = of_property_read_u32(np, "dma-channels", &sdc->num_pchans);
	if (ret && !sdc->num_pchans) {
		dev_err(&pdev->dev, "Can't get dma-channels.\n");
		return ret;
	}

	ret = of_property_read_u32(np, "dma-requests", &sdc->max_request);
	if (ret && !sdc->max_request) {
		dev_info(&pdev->dev, "Missing dma-requests, using %u.\n",
			 DMA_CHAN_MAX_DRQ_A31);
		sdc->max_request = DMA_CHAN_MAX_DRQ_A31;
	}

	/*
	 * If the number of vchans is not specified, derive it from the
	 * highest port number, at most one channel per port and direction.
	 */
	if (!sdc->num_vchans)
		sdc->num_vchans = 2 * (sdc->max_request + 1);

	sdc->pchans = devm_kcalloc(&pdev->dev, sdc->num_pchans,
				   sizeof(struct sun6i_pchan), GFP_KERNEL);
	if (!sdc->pchans)
		return -ENOMEM;

	sdc->vchans = devm_kcalloc(&pdev->dev, sdc->num_vchans,
				   sizeof(struct sun6i_vchan), GFP_KERNEL);
	if (!sdc->vchans)
		return -ENOMEM;

	tasklet_init(&sdc->task, sun6i_dma_tasklet, (unsigned long)sdc);

	for (i = 0; i < sdc->num_pchans; i++) {
		struct sun6i_pchan *pchan = &sdc->pchans[i];

		pchan->idx = i;
		pchan->base = sdc->base + 0x100 + i * 0x40;
	}

	for (i = 0; i < sdc->num_vchans; i++) {
		struct sun6i_vchan *vchan = &sdc->vchans[i];

		INIT_LIST_HEAD(&vchan->node);
		vchan->vc.desc_free = sun6i_dma_free_desc;
		vchan_init(&vchan->vc, &sdc->slave);
	}

	ret = reset_control_deassert(sdc->rstc);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't deassert the device from reset\n");
		goto err_chan_free;
	}

	ret = clk_prepare_enable(sdc->clk);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't enable the clock\n");
		goto err_reset_assert;
	}

	if (sdc->cfg->has_mbus_clk) {
		ret = clk_prepare_enable(sdc->clk_mbus);
		if (ret) {
			dev_err(&pdev->dev, "Couldn't enable mbus clock\n");
			goto err_clk_disable;
		}
	}

	ret = devm_request_irq(&pdev->dev, sdc->irq, sun6i_dma_interrupt, 0,
			       dev_name(&pdev->dev), sdc);
	if (ret) {
		dev_err(&pdev->dev, "Cannot request IRQ\n");
		goto err_mbus_clk_disable;
	}

	ret = dma_async_device_register(&sdc->slave);
	if (ret) {
		dev_warn(&pdev->dev, "Failed to register DMA engine device\n");
		goto err_irq_disable;
	}

	ret = of_dma_controller_register(pdev->dev.of_node, sun6i_dma_of_xlate,
					 sdc);
	if (ret) {
		dev_err(&pdev->dev, "of_dma_controller_register failed\n");
		goto err_dma_unregister;
	}

	if (sdc->cfg->clock_autogate_enable)
		sdc->cfg->clock_autogate_enable(sdc);

	return 0;

err_dma_unregister:
	dma_async_device_unregister(&sdc->slave);
err_irq_disable:
	sun6i_kill_tasklet(sdc);
err_mbus_clk_disable:
	clk_disable_unprepare(sdc->clk_mbus);
err_clk_disable:
	clk_disable_unprepare(sdc->clk);
err_reset_assert:
	reset_control_assert(sdc->rstc);
err_chan_free:
	sun6i_dma_free(sdc);
	return ret;
}