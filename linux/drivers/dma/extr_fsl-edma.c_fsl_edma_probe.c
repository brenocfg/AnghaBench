#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct of_device_id {struct fsl_edma_drvdata* data; } ;
struct TYPE_13__ {int directions; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_synchronize; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; TYPE_4__* dev; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct edma_regs {int /*<<< orphan*/  cr; int /*<<< orphan*/  intl; TYPE_1__* tcd; } ;
struct fsl_edma_engine {int n_chans; struct fsl_edma_drvdata const* drvdata; TYPE_3__ dma_dev; struct fsl_edma_chan* chans; int /*<<< orphan*/  big_endian; void** muxclk; void** muxbase; void* dmaclk; struct edma_regs regs; void* membase; int /*<<< orphan*/  fsl_edma_mutex; } ;
struct fsl_edma_drvdata {int dmamuxs; int (* setup_irq ) (struct platform_device*,struct fsl_edma_engine*) ;scalar_t__ has_dmaclk; } ;
struct TYPE_12__ {int /*<<< orphan*/  desc_free; } ;
struct fsl_edma_chan {int idle; TYPE_2__ vchan; int /*<<< orphan*/  dma_dir; scalar_t__ slave_id; int /*<<< orphan*/  pm_state; struct fsl_edma_engine* edma; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  csr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EDMA_CR_ERCA ; 
 int EDMA_CR_ERGA ; 
 int EINVAL ; 
 int ENOMEM ; 
 void* FSL_EDMA_BUSWIDTHS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  RUNNING ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 void* devm_clk_get (TYPE_4__*,char*) ; 
 void* devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 struct fsl_edma_engine* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_writel (struct fsl_edma_engine*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_writew (struct fsl_edma_engine*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_disable_clocks (struct fsl_edma_engine*,int) ; 
 int /*<<< orphan*/  fsl_edma_alloc_chan_resources ; 
 int /*<<< orphan*/  fsl_edma_chan_mux (struct fsl_edma_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsl_edma_dt_ids ; 
 int /*<<< orphan*/  fsl_edma_free_chan_resources ; 
 int /*<<< orphan*/  fsl_edma_free_desc ; 
 int /*<<< orphan*/  fsl_edma_issue_pending ; 
 int /*<<< orphan*/  fsl_edma_pause ; 
 int /*<<< orphan*/  fsl_edma_prep_dma_cyclic ; 
 int /*<<< orphan*/  fsl_edma_prep_slave_sg ; 
 int /*<<< orphan*/  fsl_edma_resume ; 
 int /*<<< orphan*/  fsl_edma_setup_regs (struct fsl_edma_engine*) ; 
 int /*<<< orphan*/  fsl_edma_slave_config ; 
 int /*<<< orphan*/  fsl_edma_synchronize ; 
 int /*<<< orphan*/  fsl_edma_terminate_all ; 
 int /*<<< orphan*/  fsl_edma_tx_status ; 
 int /*<<< orphan*/  fsl_edma_xlate ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_dma_controller_register (struct device_node*,int /*<<< orphan*/ ,struct fsl_edma_engine*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fsl_edma_engine*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stub1 (struct platform_device*,struct fsl_edma_engine*) ; 
 int /*<<< orphan*/  vchan_init (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int fsl_edma_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
			of_match_device(fsl_edma_dt_ids, &pdev->dev);
	struct device_node *np = pdev->dev.of_node;
	struct fsl_edma_engine *fsl_edma;
	const struct fsl_edma_drvdata *drvdata = NULL;
	struct fsl_edma_chan *fsl_chan;
	struct edma_regs *regs;
	struct resource *res;
	int len, chans;
	int ret, i;

	if (of_id)
		drvdata = of_id->data;
	if (!drvdata) {
		dev_err(&pdev->dev, "unable to find driver data\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(np, "dma-channels", &chans);
	if (ret) {
		dev_err(&pdev->dev, "Can't get dma-channels.\n");
		return ret;
	}

	len = sizeof(*fsl_edma) + sizeof(*fsl_chan) * chans;
	fsl_edma = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	if (!fsl_edma)
		return -ENOMEM;

	fsl_edma->drvdata = drvdata;
	fsl_edma->n_chans = chans;
	mutex_init(&fsl_edma->fsl_edma_mutex);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	fsl_edma->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(fsl_edma->membase))
		return PTR_ERR(fsl_edma->membase);

	fsl_edma_setup_regs(fsl_edma);
	regs = &fsl_edma->regs;

	if (drvdata->has_dmaclk) {
		fsl_edma->dmaclk = devm_clk_get(&pdev->dev, "dma");
		if (IS_ERR(fsl_edma->dmaclk)) {
			dev_err(&pdev->dev, "Missing DMA block clock.\n");
			return PTR_ERR(fsl_edma->dmaclk);
		}

		ret = clk_prepare_enable(fsl_edma->dmaclk);
		if (ret) {
			dev_err(&pdev->dev, "DMA clk block failed.\n");
			return ret;
		}
	}

	for (i = 0; i < fsl_edma->drvdata->dmamuxs; i++) {
		char clkname[32];

		res = platform_get_resource(pdev, IORESOURCE_MEM, 1 + i);
		fsl_edma->muxbase[i] = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(fsl_edma->muxbase[i])) {
			/* on error: disable all previously enabled clks */
			fsl_disable_clocks(fsl_edma, i);
			return PTR_ERR(fsl_edma->muxbase[i]);
		}

		sprintf(clkname, "dmamux%d", i);
		fsl_edma->muxclk[i] = devm_clk_get(&pdev->dev, clkname);
		if (IS_ERR(fsl_edma->muxclk[i])) {
			dev_err(&pdev->dev, "Missing DMAMUX block clock.\n");
			/* on error: disable all previously enabled clks */
			fsl_disable_clocks(fsl_edma, i);
			return PTR_ERR(fsl_edma->muxclk[i]);
		}

		ret = clk_prepare_enable(fsl_edma->muxclk[i]);
		if (ret)
			/* on error: disable all previously enabled clks */
			fsl_disable_clocks(fsl_edma, i);

	}

	fsl_edma->big_endian = of_property_read_bool(np, "big-endian");

	INIT_LIST_HEAD(&fsl_edma->dma_dev.channels);
	for (i = 0; i < fsl_edma->n_chans; i++) {
		struct fsl_edma_chan *fsl_chan = &fsl_edma->chans[i];

		fsl_chan->edma = fsl_edma;
		fsl_chan->pm_state = RUNNING;
		fsl_chan->slave_id = 0;
		fsl_chan->idle = true;
		fsl_chan->dma_dir = DMA_NONE;
		fsl_chan->vchan.desc_free = fsl_edma_free_desc;
		vchan_init(&fsl_chan->vchan, &fsl_edma->dma_dev);

		edma_writew(fsl_edma, 0x0, &regs->tcd[i].csr);
		fsl_edma_chan_mux(fsl_chan, 0, false);
	}

	edma_writel(fsl_edma, ~0, regs->intl);
	ret = fsl_edma->drvdata->setup_irq(pdev, fsl_edma);
	if (ret)
		return ret;

	dma_cap_set(DMA_PRIVATE, fsl_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_SLAVE, fsl_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, fsl_edma->dma_dev.cap_mask);

	fsl_edma->dma_dev.dev = &pdev->dev;
	fsl_edma->dma_dev.device_alloc_chan_resources
		= fsl_edma_alloc_chan_resources;
	fsl_edma->dma_dev.device_free_chan_resources
		= fsl_edma_free_chan_resources;
	fsl_edma->dma_dev.device_tx_status = fsl_edma_tx_status;
	fsl_edma->dma_dev.device_prep_slave_sg = fsl_edma_prep_slave_sg;
	fsl_edma->dma_dev.device_prep_dma_cyclic = fsl_edma_prep_dma_cyclic;
	fsl_edma->dma_dev.device_config = fsl_edma_slave_config;
	fsl_edma->dma_dev.device_pause = fsl_edma_pause;
	fsl_edma->dma_dev.device_resume = fsl_edma_resume;
	fsl_edma->dma_dev.device_terminate_all = fsl_edma_terminate_all;
	fsl_edma->dma_dev.device_synchronize = fsl_edma_synchronize;
	fsl_edma->dma_dev.device_issue_pending = fsl_edma_issue_pending;

	fsl_edma->dma_dev.src_addr_widths = FSL_EDMA_BUSWIDTHS;
	fsl_edma->dma_dev.dst_addr_widths = FSL_EDMA_BUSWIDTHS;
	fsl_edma->dma_dev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	platform_set_drvdata(pdev, fsl_edma);

	ret = dma_async_device_register(&fsl_edma->dma_dev);
	if (ret) {
		dev_err(&pdev->dev,
			"Can't register Freescale eDMA engine. (%d)\n", ret);
		fsl_disable_clocks(fsl_edma, fsl_edma->drvdata->dmamuxs);
		return ret;
	}

	ret = of_dma_controller_register(np, fsl_edma_xlate, fsl_edma);
	if (ret) {
		dev_err(&pdev->dev,
			"Can't register Freescale eDMA of_dma. (%d)\n", ret);
		dma_async_device_unregister(&fsl_edma->dma_dev);
		fsl_disable_clocks(fsl_edma, fsl_edma->drvdata->dmamuxs);
		return ret;
	}

	/* enable round robin arbitration */
	edma_writel(fsl_edma, EDMA_CR_ERGA | EDMA_CR_ERCA, regs->cr);

	return 0;
}