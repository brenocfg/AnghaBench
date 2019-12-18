#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int num_resources; int /*<<< orphan*/  dev; } ;
struct pata_pxa_pdata {int reg_shift; int /*<<< orphan*/  irq_flags; } ;
struct pata_pxa_data {int /*<<< orphan*/  dma_chan; } ;
struct dma_slave_config {int src_maxburst; int dst_maxburst; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; void* dst_addr_width; void* src_addr_width; } ;
struct TYPE_2__ {void* cmd_addr; void* command_addr; void* status_addr; void* device_addr; void* lbah_addr; void* lbam_addr; void* lbal_addr; void* nsect_addr; void* feature_addr; void* error_addr; void* data_addr; void* ctl_addr; void* altstatus_addr; void* bmdma_addr; } ;
struct ata_port {struct pata_pxa_data* private_data; TYPE_1__ ioaddr; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  pio_mask; int /*<<< orphan*/ * ops; } ;
struct ata_host {struct ata_port** ports; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_MWDMA2 ; 
 int /*<<< orphan*/  ATA_PIO4 ; 
 int ATA_REG_CMD ; 
 int ATA_REG_DATA ; 
 int ATA_REG_DEVICE ; 
 int ATA_REG_ERR ; 
 int ATA_REG_FEATURE ; 
 int ATA_REG_LBAH ; 
 int ATA_REG_LBAL ; 
 int ATA_REG_LBAM ; 
 int ATA_REG_NSECT ; 
 int ATA_REG_STATUS ; 
 void* DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int ata_host_activate (struct ata_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ata_host* ata_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ata_sff_interrupt ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct pata_pxa_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 void* devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pata_pxa_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel (int /*<<< orphan*/ *,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pxa_ata_port_ops ; 
 int /*<<< orphan*/  pxa_ata_sht ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_ata_probe(struct platform_device *pdev)
{
	struct ata_host *host;
	struct ata_port *ap;
	struct pata_pxa_data *data;
	struct resource *cmd_res;
	struct resource *ctl_res;
	struct resource *dma_res;
	struct resource *irq_res;
	struct pata_pxa_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct dma_slave_config	config;
	int ret = 0;

	/*
	 * Resource validation, three resources are needed:
	 *  - CMD port base address
	 *  - CTL port base address
	 *  - DMA port base address
	 *  - IRQ pin
	 */
	if (pdev->num_resources != 4) {
		dev_err(&pdev->dev, "invalid number of resources\n");
		return -EINVAL;
	}

	/*
	 * CMD port base address
	 */
	cmd_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(cmd_res == NULL))
		return -EINVAL;

	/*
	 * CTL port base address
	 */
	ctl_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (unlikely(ctl_res == NULL))
		return -EINVAL;

	/*
	 * DMA port base address
	 */
	dma_res = platform_get_resource(pdev, IORESOURCE_DMA, 0);
	if (unlikely(dma_res == NULL))
		return -EINVAL;

	/*
	 * IRQ pin
	 */
	irq_res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (unlikely(irq_res == NULL))
		return -EINVAL;

	/*
	 * Allocate the host
	 */
	host = ata_host_alloc(&pdev->dev, 1);
	if (!host)
		return -ENOMEM;

	ap		= host->ports[0];
	ap->ops		= &pxa_ata_port_ops;
	ap->pio_mask	= ATA_PIO4;
	ap->mwdma_mask	= ATA_MWDMA2;

	ap->ioaddr.cmd_addr	= devm_ioremap(&pdev->dev, cmd_res->start,
						resource_size(cmd_res));
	ap->ioaddr.ctl_addr	= devm_ioremap(&pdev->dev, ctl_res->start,
						resource_size(ctl_res));
	ap->ioaddr.bmdma_addr	= devm_ioremap(&pdev->dev, dma_res->start,
						resource_size(dma_res));

	/*
	 * Adjust register offsets
	 */
	ap->ioaddr.altstatus_addr = ap->ioaddr.ctl_addr;
	ap->ioaddr.data_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_DATA << pdata->reg_shift);
	ap->ioaddr.error_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_ERR << pdata->reg_shift);
	ap->ioaddr.feature_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_FEATURE << pdata->reg_shift);
	ap->ioaddr.nsect_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_NSECT << pdata->reg_shift);
	ap->ioaddr.lbal_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_LBAL << pdata->reg_shift);
	ap->ioaddr.lbam_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_LBAM << pdata->reg_shift);
	ap->ioaddr.lbah_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_LBAH << pdata->reg_shift);
	ap->ioaddr.device_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_DEVICE << pdata->reg_shift);
	ap->ioaddr.status_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_STATUS << pdata->reg_shift);
	ap->ioaddr.command_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_CMD << pdata->reg_shift);

	/*
	 * Allocate and load driver's internal data structure
	 */
	data = devm_kzalloc(&pdev->dev, sizeof(struct pata_pxa_data),
								GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ap->private_data = data;

	memset(&config, 0, sizeof(config));
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.src_addr = dma_res->start;
	config.dst_addr = dma_res->start;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;

	/*
	 * Request the DMA channel
	 */
	data->dma_chan =
		dma_request_slave_channel(&pdev->dev, "data");
	if (!data->dma_chan)
		return -EBUSY;
	ret = dmaengine_slave_config(data->dma_chan, &config);
	if (ret < 0) {
		dev_err(&pdev->dev, "dma configuration failed: %d\n", ret);
		return ret;
	}

	/*
	 * Activate the ATA host
	 */
	ret = ata_host_activate(host, irq_res->start, ata_sff_interrupt,
				pdata->irq_flags, &pxa_ata_sht);
	if (ret)
		dma_release_channel(data->dma_chan);

	return ret;
}