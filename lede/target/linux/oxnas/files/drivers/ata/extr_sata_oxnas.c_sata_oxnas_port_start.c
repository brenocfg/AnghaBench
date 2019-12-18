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
struct sgdma_request {int dummy; } ;
struct sata_oxnas_port_priv {void* sgdma_request; void* sgdma_request_pa; int /*<<< orphan*/  core_base; scalar_t__ sgdma_base; scalar_t__ dmactl_base; scalar_t__ port_base; } ;
struct sata_oxnas_host_priv {int dma_size; int n_ports; void* dma_base; int /*<<< orphan*/  core_base; scalar_t__ sgdma_base; scalar_t__ dmactl_base; scalar_t__ port_base; } ;
struct device {int dummy; } ;
struct ata_port {struct sata_oxnas_port_priv* private_data; void* bmdma_prd; void* bmdma_prd_dma; scalar_t__ port_no; TYPE_1__* host; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {struct device* dev; struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CORESIZE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PORT_SIZE ; 
 int SATA_OXNAS_DMA_SIZE ; 
 int /*<<< orphan*/  SGDMA_CORESIZE ; 
 void* dma_alloc_coherent (struct device*,int,void**,int /*<<< orphan*/ ) ; 
 void* ioremap (void*,int) ; 
 int /*<<< orphan*/  kfree (struct sata_oxnas_port_priv*) ; 
 struct sata_oxnas_port_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_oxnas_post_reset_init (struct ata_port*) ; 

__attribute__((used)) static int sata_oxnas_port_start(struct ata_port *ap)
{
	struct sata_oxnas_host_priv *host_priv = ap->host->private_data;
	struct device *dev = ap->host->dev;
	struct sata_oxnas_port_priv *pp;
	void *mem;
	dma_addr_t mem_dma;

	DPRINTK("ENTER\n");

	pp = kzalloc(sizeof(*pp), GFP_KERNEL);
	if (!pp)
		return -ENOMEM;

	pp->port_base = host_priv->port_base +
			(ap->port_no ? PORT_SIZE : 0);
	pp->dmactl_base = host_priv->dmactl_base +
			 (ap->port_no ? DMA_CORESIZE : 0);
	pp->sgdma_base = host_priv->sgdma_base +
			 (ap->port_no ? SGDMA_CORESIZE : 0);
	pp->core_base = host_priv->core_base;

	/* preallocated */
	if (host_priv->dma_size >= SATA_OXNAS_DMA_SIZE * host_priv->n_ports) {
		DPRINTK("using preallocated DMA\n");
		mem_dma = host_priv->dma_base +
				(ap->port_no ? SATA_OXNAS_DMA_SIZE : 0);
		mem = ioremap(mem_dma, SATA_OXNAS_DMA_SIZE);
	} else {
		mem = dma_alloc_coherent(dev, SATA_OXNAS_DMA_SIZE, &mem_dma,
					 GFP_KERNEL);
	}
	if (!mem)
		goto err_ret;

	pp->sgdma_request_pa = mem_dma;
	pp->sgdma_request = mem;

	ap->bmdma_prd_dma = mem_dma + sizeof(struct sgdma_request);
	ap->bmdma_prd = mem + sizeof(struct sgdma_request);

	ap->private_data = pp;

	sata_oxnas_post_reset_init(ap);

	return 0;

err_ret:
	kfree(pp);
	return -ENOMEM;

}