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
struct TYPE_11__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_12__ {TYPE_2__* dev; int /*<<< orphan*/  copy_align; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct mmp_tdma_device {TYPE_3__ device; int /*<<< orphan*/  base; TYPE_2__* dev; } ;
struct gen_pool {int dummy; } ;
typedef  enum mmp_tdma_type { ____Placeholder_mmp_tdma_type } mmp_tdma_type ;
struct TYPE_10__ {int driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAENGINE_ALIGN_8_BYTES ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TDMA_CHANNEL_NUM ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct mmp_tdma_device* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mmp_tdma_device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dmaenginem_async_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  mmp_tdma_alloc_chan_resources ; 
 int mmp_tdma_chan_init (struct mmp_tdma_device*,int,int,int,struct gen_pool*) ; 
 int /*<<< orphan*/  mmp_tdma_config ; 
 int /*<<< orphan*/  mmp_tdma_dt_ids ; 
 int /*<<< orphan*/  mmp_tdma_free_chan_resources ; 
 int /*<<< orphan*/  mmp_tdma_int_handler ; 
 int /*<<< orphan*/  mmp_tdma_issue_pending ; 
 int /*<<< orphan*/  mmp_tdma_pause_chan ; 
 int /*<<< orphan*/  mmp_tdma_prep_dma_cyclic ; 
 int /*<<< orphan*/  mmp_tdma_resume_chan ; 
 int /*<<< orphan*/  mmp_tdma_terminate_all ; 
 int /*<<< orphan*/  mmp_tdma_tx_status ; 
 int /*<<< orphan*/  mmp_tdma_xlate ; 
 int of_dma_controller_register (scalar_t__,int /*<<< orphan*/ ,struct mmp_tdma_device*) ; 
 struct gen_pool* of_gen_pool_get (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmp_tdma_device*) ; 
 struct gen_pool* sram_get_gpool (char*) ; 

__attribute__((used)) static int mmp_tdma_probe(struct platform_device *pdev)
{
	enum mmp_tdma_type type;
	const struct of_device_id *of_id;
	struct mmp_tdma_device *tdev;
	struct resource *iores;
	int i, ret;
	int irq = 0, irq_num = 0;
	int chan_num = TDMA_CHANNEL_NUM;
	struct gen_pool *pool = NULL;

	of_id = of_match_device(mmp_tdma_dt_ids, &pdev->dev);
	if (of_id)
		type = (enum mmp_tdma_type) of_id->data;
	else
		type = platform_get_device_id(pdev)->driver_data;

	/* always have couple channels */
	tdev = devm_kzalloc(&pdev->dev, sizeof(*tdev), GFP_KERNEL);
	if (!tdev)
		return -ENOMEM;

	tdev->dev = &pdev->dev;

	for (i = 0; i < chan_num; i++) {
		if (platform_get_irq(pdev, i) > 0)
			irq_num++;
	}

	iores = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	tdev->base = devm_ioremap_resource(&pdev->dev, iores);
	if (IS_ERR(tdev->base))
		return PTR_ERR(tdev->base);

	INIT_LIST_HEAD(&tdev->device.channels);

	if (pdev->dev.of_node)
		pool = of_gen_pool_get(pdev->dev.of_node, "asram", 0);
	else
		pool = sram_get_gpool("asram");
	if (!pool) {
		dev_err(&pdev->dev, "asram pool not available\n");
		return -ENOMEM;
	}

	if (irq_num != chan_num) {
		irq = platform_get_irq(pdev, 0);
		ret = devm_request_irq(&pdev->dev, irq,
			mmp_tdma_int_handler, 0, "tdma", tdev);
		if (ret)
			return ret;
	}

	/* initialize channel parameters */
	for (i = 0; i < chan_num; i++) {
		irq = (irq_num != chan_num) ? 0 : platform_get_irq(pdev, i);
		ret = mmp_tdma_chan_init(tdev, i, irq, type, pool);
		if (ret)
			return ret;
	}

	dma_cap_set(DMA_SLAVE, tdev->device.cap_mask);
	dma_cap_set(DMA_CYCLIC, tdev->device.cap_mask);
	tdev->device.dev = &pdev->dev;
	tdev->device.device_alloc_chan_resources =
					mmp_tdma_alloc_chan_resources;
	tdev->device.device_free_chan_resources =
					mmp_tdma_free_chan_resources;
	tdev->device.device_prep_dma_cyclic = mmp_tdma_prep_dma_cyclic;
	tdev->device.device_tx_status = mmp_tdma_tx_status;
	tdev->device.device_issue_pending = mmp_tdma_issue_pending;
	tdev->device.device_config = mmp_tdma_config;
	tdev->device.device_pause = mmp_tdma_pause_chan;
	tdev->device.device_resume = mmp_tdma_resume_chan;
	tdev->device.device_terminate_all = mmp_tdma_terminate_all;
	tdev->device.copy_align = DMAENGINE_ALIGN_8_BYTES;

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	platform_set_drvdata(pdev, tdev);

	ret = dmaenginem_async_device_register(&tdev->device);
	if (ret) {
		dev_err(tdev->device.dev, "unable to register\n");
		return ret;
	}

	if (pdev->dev.of_node) {
		ret = of_dma_controller_register(pdev->dev.of_node,
							mmp_tdma_xlate, tdev);
		if (ret) {
			dev_err(tdev->device.dev,
				"failed to register controller\n");
			return ret;
		}
	}

	dev_info(tdev->device.dev, "initialized\n");
	return 0;
}