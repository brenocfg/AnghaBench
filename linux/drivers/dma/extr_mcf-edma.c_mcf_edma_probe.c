#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mcf_edma_platform_data {int dma_channels; int /*<<< orphan*/  slavecnt; int /*<<< orphan*/  slave_map; } ;
struct TYPE_8__ {int /*<<< orphan*/  mapcnt; int /*<<< orphan*/  map; int /*<<< orphan*/  fn; } ;
struct TYPE_10__ {int directions; TYPE_2__ filter; void* dst_addr_widths; void* src_addr_widths; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_prep_dma_cyclic; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/ * dev; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct edma_regs {int /*<<< orphan*/ * cr; int /*<<< orphan*/ * intl; int /*<<< orphan*/ * inth; TYPE_1__* tcd; } ;
struct fsl_edma_engine {int n_chans; int big_endian; TYPE_4__ dma_dev; TYPE_5__* drvdata; struct fsl_edma_chan* chans; struct edma_regs regs; int /*<<< orphan*/  membase; int /*<<< orphan*/  fsl_edma_mutex; } ;
struct TYPE_9__ {int /*<<< orphan*/  desc_free; } ;
struct fsl_edma_chan {int slave_id; int idle; TYPE_3__ vchan; int /*<<< orphan*/  dma_dir; struct fsl_edma_engine* edma; } ;
struct TYPE_11__ {int (* setup_irq ) (struct platform_device*,struct fsl_edma_engine*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  csr; } ;

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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct mcf_edma_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct fsl_edma_engine* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_async_device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_edma_alloc_chan_resources ; 
 int /*<<< orphan*/  fsl_edma_free_chan_resources ; 
 int /*<<< orphan*/  fsl_edma_free_desc ; 
 int /*<<< orphan*/  fsl_edma_issue_pending ; 
 int /*<<< orphan*/  fsl_edma_pause ; 
 int /*<<< orphan*/  fsl_edma_prep_dma_cyclic ; 
 int /*<<< orphan*/  fsl_edma_prep_slave_sg ; 
 int /*<<< orphan*/  fsl_edma_resume ; 
 int /*<<< orphan*/  fsl_edma_setup_regs (struct fsl_edma_engine*) ; 
 int /*<<< orphan*/  fsl_edma_slave_config ; 
 int /*<<< orphan*/  fsl_edma_terminate_all ; 
 int /*<<< orphan*/  fsl_edma_tx_status ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 TYPE_5__ mcf_data ; 
 int /*<<< orphan*/  mcf_edma_filter_fn ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fsl_edma_engine*) ; 
 int stub1 (struct platform_device*,struct fsl_edma_engine*) ; 
 int /*<<< orphan*/  vchan_init (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int mcf_edma_probe(struct platform_device *pdev)
{
	struct mcf_edma_platform_data *pdata;
	struct fsl_edma_engine *mcf_edma;
	struct fsl_edma_chan *mcf_chan;
	struct edma_regs *regs;
	struct resource *res;
	int ret, i, len, chans;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(&pdev->dev, "no platform data supplied\n");
		return -EINVAL;
	}

	chans = pdata->dma_channels;
	len = sizeof(*mcf_edma) + sizeof(*mcf_chan) * chans;
	mcf_edma = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	if (!mcf_edma)
		return -ENOMEM;

	mcf_edma->n_chans = chans;

	/* Set up drvdata for ColdFire edma */
	mcf_edma->drvdata = &mcf_data;
	mcf_edma->big_endian = 1;

	if (!mcf_edma->n_chans) {
		dev_info(&pdev->dev, "setting default channel number to 64");
		mcf_edma->n_chans = 64;
	}

	mutex_init(&mcf_edma->fsl_edma_mutex);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	mcf_edma->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mcf_edma->membase))
		return PTR_ERR(mcf_edma->membase);

	fsl_edma_setup_regs(mcf_edma);
	regs = &mcf_edma->regs;

	INIT_LIST_HEAD(&mcf_edma->dma_dev.channels);
	for (i = 0; i < mcf_edma->n_chans; i++) {
		struct fsl_edma_chan *mcf_chan = &mcf_edma->chans[i];

		mcf_chan->edma = mcf_edma;
		mcf_chan->slave_id = i;
		mcf_chan->idle = true;
		mcf_chan->dma_dir = DMA_NONE;
		mcf_chan->vchan.desc_free = fsl_edma_free_desc;
		vchan_init(&mcf_chan->vchan, &mcf_edma->dma_dev);
		iowrite32(0x0, &regs->tcd[i].csr);
	}

	iowrite32(~0, regs->inth);
	iowrite32(~0, regs->intl);

	ret = mcf_edma->drvdata->setup_irq(pdev, mcf_edma);
	if (ret)
		return ret;

	dma_cap_set(DMA_PRIVATE, mcf_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_SLAVE, mcf_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, mcf_edma->dma_dev.cap_mask);

	mcf_edma->dma_dev.dev = &pdev->dev;
	mcf_edma->dma_dev.device_alloc_chan_resources =
			fsl_edma_alloc_chan_resources;
	mcf_edma->dma_dev.device_free_chan_resources =
			fsl_edma_free_chan_resources;
	mcf_edma->dma_dev.device_config = fsl_edma_slave_config;
	mcf_edma->dma_dev.device_prep_dma_cyclic =
			fsl_edma_prep_dma_cyclic;
	mcf_edma->dma_dev.device_prep_slave_sg = fsl_edma_prep_slave_sg;
	mcf_edma->dma_dev.device_tx_status = fsl_edma_tx_status;
	mcf_edma->dma_dev.device_pause = fsl_edma_pause;
	mcf_edma->dma_dev.device_resume = fsl_edma_resume;
	mcf_edma->dma_dev.device_terminate_all = fsl_edma_terminate_all;
	mcf_edma->dma_dev.device_issue_pending = fsl_edma_issue_pending;

	mcf_edma->dma_dev.src_addr_widths = FSL_EDMA_BUSWIDTHS;
	mcf_edma->dma_dev.dst_addr_widths = FSL_EDMA_BUSWIDTHS;
	mcf_edma->dma_dev.directions =
			BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	mcf_edma->dma_dev.filter.fn = mcf_edma_filter_fn;
	mcf_edma->dma_dev.filter.map = pdata->slave_map;
	mcf_edma->dma_dev.filter.mapcnt = pdata->slavecnt;

	platform_set_drvdata(pdev, mcf_edma);

	ret = dma_async_device_register(&mcf_edma->dma_dev);
	if (ret) {
		dev_err(&pdev->dev,
			"Can't register Freescale eDMA engine. (%d)\n", ret);
		return ret;
	}

	/* Enable round robin arbitration */
	iowrite32(EDMA_CR_ERGA | EDMA_CR_ERCA, regs->cr);

	return 0;
}