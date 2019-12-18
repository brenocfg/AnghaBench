#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {unsigned int driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct pch_dma_regs {int /*<<< orphan*/ * desc; } ;
struct pch_dma_desc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct pch_dma_chan {TYPE_1__ chan; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  free_list; int /*<<< orphan*/  queue; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lock; int /*<<< orphan*/ * membase; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; int /*<<< orphan*/ * dev; } ;
struct pch_dma {struct pch_dma_regs* membase; int /*<<< orphan*/  pool; TYPE_2__ dma; struct pch_dma_chan* channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dma_async_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pch_dma*) ; 
 int /*<<< orphan*/  kfree (struct pch_dma*) ; 
 struct pch_dma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct pch_dma_regs* pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,struct pch_dma_regs*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pch_dma*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pd_alloc_chan_resources ; 
 int /*<<< orphan*/  pd_device_terminate_all ; 
 int /*<<< orphan*/  pd_free_chan_resources ; 
 int /*<<< orphan*/  pd_irq ; 
 int /*<<< orphan*/  pd_issue_pending ; 
 int /*<<< orphan*/  pd_prep_slave_sg ; 
 int /*<<< orphan*/  pd_tx_status ; 
 int /*<<< orphan*/  pdc_tasklet ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pch_dma*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int pch_dma_probe(struct pci_dev *pdev,
				   const struct pci_device_id *id)
{
	struct pch_dma *pd;
	struct pch_dma_regs *regs;
	unsigned int nr_channels;
	int err;
	int i;

	nr_channels = id->driver_data;
	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return -ENOMEM;

	pci_set_drvdata(pdev, pd);

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "Cannot enable PCI device\n");
		goto err_free_mem;
	}

	if (!(pci_resource_flags(pdev, 1) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev, "Cannot find proper base address\n");
		err = -ENODEV;
		goto err_disable_pdev;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(&pdev->dev, "Cannot obtain PCI resources\n");
		goto err_disable_pdev;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (err) {
		dev_err(&pdev->dev, "Cannot set proper DMA config\n");
		goto err_free_res;
	}

	regs = pd->membase = pci_iomap(pdev, 1, 0);
	if (!pd->membase) {
		dev_err(&pdev->dev, "Cannot map MMIO registers\n");
		err = -ENOMEM;
		goto err_free_res;
	}

	pci_set_master(pdev);

	err = request_irq(pdev->irq, pd_irq, IRQF_SHARED, DRV_NAME, pd);
	if (err) {
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		goto err_iounmap;
	}

	pd->pool = dma_pool_create("pch_dma_desc_pool", &pdev->dev,
				   sizeof(struct pch_dma_desc), 4, 0);
	if (!pd->pool) {
		dev_err(&pdev->dev, "Failed to alloc DMA descriptors\n");
		err = -ENOMEM;
		goto err_free_irq;
	}

	pd->dma.dev = &pdev->dev;

	INIT_LIST_HEAD(&pd->dma.channels);

	for (i = 0; i < nr_channels; i++) {
		struct pch_dma_chan *pd_chan = &pd->channels[i];

		pd_chan->chan.device = &pd->dma;
		dma_cookie_init(&pd_chan->chan);

		pd_chan->membase = &regs->desc[i];

		spin_lock_init(&pd_chan->lock);

		INIT_LIST_HEAD(&pd_chan->active_list);
		INIT_LIST_HEAD(&pd_chan->queue);
		INIT_LIST_HEAD(&pd_chan->free_list);

		tasklet_init(&pd_chan->tasklet, pdc_tasklet,
			     (unsigned long)pd_chan);
		list_add_tail(&pd_chan->chan.device_node, &pd->dma.channels);
	}

	dma_cap_zero(pd->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, pd->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, pd->dma.cap_mask);

	pd->dma.device_alloc_chan_resources = pd_alloc_chan_resources;
	pd->dma.device_free_chan_resources = pd_free_chan_resources;
	pd->dma.device_tx_status = pd_tx_status;
	pd->dma.device_issue_pending = pd_issue_pending;
	pd->dma.device_prep_slave_sg = pd_prep_slave_sg;
	pd->dma.device_terminate_all = pd_device_terminate_all;

	err = dma_async_device_register(&pd->dma);
	if (err) {
		dev_err(&pdev->dev, "Failed to register DMA device\n");
		goto err_free_pool;
	}

	return 0;

err_free_pool:
	dma_pool_destroy(pd->pool);
err_free_irq:
	free_irq(pdev->irq, pd);
err_iounmap:
	pci_iounmap(pdev, pd->membase);
err_free_res:
	pci_release_regions(pdev);
err_disable_pdev:
	pci_disable_device(pdev);
err_free_mem:
	kfree(pd);
	return err;
}