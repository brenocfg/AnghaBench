#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_submit; } ;
struct mv_xor_v2_sw_desc {int idx; int /*<<< orphan*/  free_list; TYPE_2__ async_tx; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct dma_device {int max_xor; int /*<<< orphan*/  channels; int /*<<< orphan*/  device_prep_dma_xor; int /*<<< orphan*/  device_prep_dma_interrupt; int /*<<< orphan*/  device_prep_dma_memcpy; int /*<<< orphan*/ * dev; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  cap_mask; } ;
struct mv_xor_v2_device {int desc_size; void* reg_clk; void* clk; int /*<<< orphan*/  hw_desq; int /*<<< orphan*/  hw_desq_virt; TYPE_1__ dmachan; struct dma_device dmadev; int /*<<< orphan*/  free_sw_desc; struct mv_xor_v2_sw_desc* sw_desq; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_tasklet; struct msi_desc* msi_desc; void* glob_base; void* dma_base; } ;
struct mv_xor_v2_descriptor {int dummy; } ;
struct msi_desc {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_INTERRUPT ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_XOR ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int MV_XOR_V2_DESC_NUM ; 
 int MV_XOR_V2_EXT_DESC_SIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  async_tx_ack (TYPE_2__*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct mv_xor_v2_sw_desc* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct mv_xor_v2_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mv_xor_v2_device*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_cookie_status ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct msi_desc* first_msi_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_xor_v2_descq_init (struct mv_xor_v2_device*) ; 
 int /*<<< orphan*/  mv_xor_v2_enable_imsg_thrd (struct mv_xor_v2_device*) ; 
 int /*<<< orphan*/  mv_xor_v2_interrupt_handler ; 
 int /*<<< orphan*/  mv_xor_v2_issue_pending ; 
 int /*<<< orphan*/  mv_xor_v2_prep_dma_interrupt ; 
 int /*<<< orphan*/  mv_xor_v2_prep_dma_memcpy ; 
 int /*<<< orphan*/  mv_xor_v2_prep_dma_xor ; 
 int mv_xor_v2_set_desc_size (struct mv_xor_v2_device*) ; 
 int /*<<< orphan*/  mv_xor_v2_set_msi_msg ; 
 int /*<<< orphan*/  mv_xor_v2_tasklet ; 
 int /*<<< orphan*/  mv_xor_v2_tx_submit ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int platform_msi_domain_alloc_irqs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_msi_domain_free_irqs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mv_xor_v2_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mv_xor_v2_probe(struct platform_device *pdev)
{
	struct mv_xor_v2_device *xor_dev;
	struct resource *res;
	int i, ret = 0;
	struct dma_device *dma_dev;
	struct mv_xor_v2_sw_desc *sw_desc;
	struct msi_desc *msi_desc;

	BUILD_BUG_ON(sizeof(struct mv_xor_v2_descriptor) !=
		     MV_XOR_V2_EXT_DESC_SIZE);

	xor_dev = devm_kzalloc(&pdev->dev, sizeof(*xor_dev), GFP_KERNEL);
	if (!xor_dev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xor_dev->dma_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xor_dev->dma_base))
		return PTR_ERR(xor_dev->dma_base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	xor_dev->glob_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xor_dev->glob_base))
		return PTR_ERR(xor_dev->glob_base);

	platform_set_drvdata(pdev, xor_dev);

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40));
	if (ret)
		return ret;

	xor_dev->reg_clk = devm_clk_get(&pdev->dev, "reg");
	if (PTR_ERR(xor_dev->reg_clk) != -ENOENT) {
		if (!IS_ERR(xor_dev->reg_clk)) {
			ret = clk_prepare_enable(xor_dev->reg_clk);
			if (ret)
				return ret;
		} else {
			return PTR_ERR(xor_dev->reg_clk);
		}
	}

	xor_dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(xor_dev->clk) && PTR_ERR(xor_dev->clk) == -EPROBE_DEFER) {
		ret = EPROBE_DEFER;
		goto disable_reg_clk;
	}
	if (!IS_ERR(xor_dev->clk)) {
		ret = clk_prepare_enable(xor_dev->clk);
		if (ret)
			goto disable_reg_clk;
	}

	ret = platform_msi_domain_alloc_irqs(&pdev->dev, 1,
					     mv_xor_v2_set_msi_msg);
	if (ret)
		goto disable_clk;

	msi_desc = first_msi_entry(&pdev->dev);
	if (!msi_desc)
		goto free_msi_irqs;
	xor_dev->msi_desc = msi_desc;

	ret = devm_request_irq(&pdev->dev, msi_desc->irq,
			       mv_xor_v2_interrupt_handler, 0,
			       dev_name(&pdev->dev), xor_dev);
	if (ret)
		goto free_msi_irqs;

	tasklet_init(&xor_dev->irq_tasklet, mv_xor_v2_tasklet,
		     (unsigned long) xor_dev);

	xor_dev->desc_size = mv_xor_v2_set_desc_size(xor_dev);

	dma_cookie_init(&xor_dev->dmachan);

	/*
	 * allocate coherent memory for hardware descriptors
	 * note: writecombine gives slightly better performance, but
	 * requires that we explicitly flush the writes
	 */
	xor_dev->hw_desq_virt =
		dma_alloc_coherent(&pdev->dev,
				   xor_dev->desc_size * MV_XOR_V2_DESC_NUM,
				   &xor_dev->hw_desq, GFP_KERNEL);
	if (!xor_dev->hw_desq_virt) {
		ret = -ENOMEM;
		goto free_msi_irqs;
	}

	/* alloc memory for the SW descriptors */
	xor_dev->sw_desq = devm_kcalloc(&pdev->dev,
					MV_XOR_V2_DESC_NUM, sizeof(*sw_desc),
					GFP_KERNEL);
	if (!xor_dev->sw_desq) {
		ret = -ENOMEM;
		goto free_hw_desq;
	}

	spin_lock_init(&xor_dev->lock);

	/* init the free SW descriptors list */
	INIT_LIST_HEAD(&xor_dev->free_sw_desc);

	/* add all SW descriptors to the free list */
	for (i = 0; i < MV_XOR_V2_DESC_NUM; i++) {
		struct mv_xor_v2_sw_desc *sw_desc =
			xor_dev->sw_desq + i;
		sw_desc->idx = i;
		dma_async_tx_descriptor_init(&sw_desc->async_tx,
					     &xor_dev->dmachan);
		sw_desc->async_tx.tx_submit = mv_xor_v2_tx_submit;
		async_tx_ack(&sw_desc->async_tx);

		list_add(&sw_desc->free_list,
			 &xor_dev->free_sw_desc);
	}

	dma_dev = &xor_dev->dmadev;

	/* set DMA capabilities */
	dma_cap_zero(dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	dma_cap_set(DMA_INTERRUPT, dma_dev->cap_mask);

	/* init dma link list */
	INIT_LIST_HEAD(&dma_dev->channels);

	/* set base routines */
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = mv_xor_v2_issue_pending;
	dma_dev->dev = &pdev->dev;

	dma_dev->device_prep_dma_memcpy = mv_xor_v2_prep_dma_memcpy;
	dma_dev->device_prep_dma_interrupt = mv_xor_v2_prep_dma_interrupt;
	dma_dev->max_xor = 8;
	dma_dev->device_prep_dma_xor = mv_xor_v2_prep_dma_xor;

	xor_dev->dmachan.device = dma_dev;

	list_add_tail(&xor_dev->dmachan.device_node,
		      &dma_dev->channels);

	mv_xor_v2_enable_imsg_thrd(xor_dev);

	mv_xor_v2_descq_init(xor_dev);

	ret = dma_async_device_register(dma_dev);
	if (ret)
		goto free_hw_desq;

	dev_notice(&pdev->dev, "Marvell Version 2 XOR driver\n");

	return 0;

free_hw_desq:
	dma_free_coherent(&pdev->dev,
			  xor_dev->desc_size * MV_XOR_V2_DESC_NUM,
			  xor_dev->hw_desq_virt, xor_dev->hw_desq);
free_msi_irqs:
	platform_msi_domain_free_irqs(&pdev->dev);
disable_clk:
	clk_disable_unprepare(xor_dev->clk);
disable_reg_clk:
	clk_disable_unprepare(xor_dev->reg_clk);
	return ret;
}