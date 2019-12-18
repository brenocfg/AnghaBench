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
struct timb_dma_platform_data_channel {int rx; int /*<<< orphan*/  bytes_per_line; int /*<<< orphan*/  descriptor_elements; int /*<<< orphan*/  descriptors; } ;
struct timb_dma_platform_data {int nr_channels; struct timb_dma_platform_data_channel* channels; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct timb_dma_chan {TYPE_1__ chan; scalar_t__ membase; int /*<<< orphan*/  direction; int /*<<< orphan*/  bytes_per_line; int /*<<< orphan*/  desc_elems; int /*<<< orphan*/  descs; int /*<<< orphan*/  free_list; int /*<<< orphan*/  queue; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  channels; int /*<<< orphan*/ * dev; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; } ;
struct timb_dma {scalar_t__ membase; int /*<<< orphan*/  tasklet; TYPE_2__ dma; struct timb_dma_chan* channels; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int TIMBDMA_32BIT_ADDR ; 
 scalar_t__ TIMBDMA_ACR ; 
 scalar_t__ TIMBDMA_IER ; 
 int TIMBDMA_INSTANCE_OFFSET ; 
 scalar_t__ TIMBDMA_INSTANCE_TX_OFFSET ; 
 scalar_t__ TIMBDMA_ISR ; 
 int /*<<< orphan*/  channels ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct timb_dma_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int dma_async_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_1__*) ; 
 int /*<<< orphan*/  free_irq (int,struct timb_dma*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct timb_dma*) ; 
 struct timb_dma* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct timb_dma*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timb_dma*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct timb_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td_alloc_chan_resources ; 
 int /*<<< orphan*/  td_free_chan_resources ; 
 int /*<<< orphan*/  td_irq ; 
 int /*<<< orphan*/  td_issue_pending ; 
 int /*<<< orphan*/  td_prep_slave_sg ; 
 int /*<<< orphan*/  td_tasklet ; 
 int /*<<< orphan*/  td_terminate_all ; 
 int /*<<< orphan*/  td_tx_status ; 

__attribute__((used)) static int td_probe(struct platform_device *pdev)
{
	struct timb_dma_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct timb_dma *td;
	struct resource *iomem;
	int irq;
	int err;
	int i;

	if (!pdata) {
		dev_err(&pdev->dev, "No platform data\n");
		return -EINVAL;
	}

	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!iomem)
		return -EINVAL;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	if (!request_mem_region(iomem->start, resource_size(iomem),
		DRIVER_NAME))
		return -EBUSY;

	td  = kzalloc(struct_size(td, channels, pdata->nr_channels),
		      GFP_KERNEL);
	if (!td) {
		err = -ENOMEM;
		goto err_release_region;
	}

	dev_dbg(&pdev->dev, "Allocated TD: %p\n", td);

	td->membase = ioremap(iomem->start, resource_size(iomem));
	if (!td->membase) {
		dev_err(&pdev->dev, "Failed to remap I/O memory\n");
		err = -ENOMEM;
		goto err_free_mem;
	}

	/* 32bit addressing */
	iowrite32(TIMBDMA_32BIT_ADDR, td->membase + TIMBDMA_ACR);

	/* disable and clear any interrupts */
	iowrite32(0x0, td->membase + TIMBDMA_IER);
	iowrite32(0xFFFFFFFF, td->membase + TIMBDMA_ISR);

	tasklet_init(&td->tasklet, td_tasklet, (unsigned long)td);

	err = request_irq(irq, td_irq, IRQF_SHARED, DRIVER_NAME, td);
	if (err) {
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		goto err_tasklet_kill;
	}

	td->dma.device_alloc_chan_resources	= td_alloc_chan_resources;
	td->dma.device_free_chan_resources	= td_free_chan_resources;
	td->dma.device_tx_status		= td_tx_status;
	td->dma.device_issue_pending		= td_issue_pending;

	dma_cap_set(DMA_SLAVE, td->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, td->dma.cap_mask);
	td->dma.device_prep_slave_sg = td_prep_slave_sg;
	td->dma.device_terminate_all = td_terminate_all;

	td->dma.dev = &pdev->dev;

	INIT_LIST_HEAD(&td->dma.channels);

	for (i = 0; i < pdata->nr_channels; i++) {
		struct timb_dma_chan *td_chan = &td->channels[i];
		struct timb_dma_platform_data_channel *pchan =
			pdata->channels + i;

		/* even channels are RX, odd are TX */
		if ((i % 2) == pchan->rx) {
			dev_err(&pdev->dev, "Wrong channel configuration\n");
			err = -EINVAL;
			goto err_free_irq;
		}

		td_chan->chan.device = &td->dma;
		dma_cookie_init(&td_chan->chan);
		spin_lock_init(&td_chan->lock);
		INIT_LIST_HEAD(&td_chan->active_list);
		INIT_LIST_HEAD(&td_chan->queue);
		INIT_LIST_HEAD(&td_chan->free_list);

		td_chan->descs = pchan->descriptors;
		td_chan->desc_elems = pchan->descriptor_elements;
		td_chan->bytes_per_line = pchan->bytes_per_line;
		td_chan->direction = pchan->rx ? DMA_DEV_TO_MEM :
			DMA_MEM_TO_DEV;

		td_chan->membase = td->membase +
			(i / 2) * TIMBDMA_INSTANCE_OFFSET +
			(pchan->rx ? 0 : TIMBDMA_INSTANCE_TX_OFFSET);

		dev_dbg(&pdev->dev, "Chan: %d, membase: %p\n",
			i, td_chan->membase);

		list_add_tail(&td_chan->chan.device_node, &td->dma.channels);
	}

	err = dma_async_device_register(&td->dma);
	if (err) {
		dev_err(&pdev->dev, "Failed to register async device\n");
		goto err_free_irq;
	}

	platform_set_drvdata(pdev, td);

	dev_dbg(&pdev->dev, "Probe result: %d\n", err);
	return err;

err_free_irq:
	free_irq(irq, td);
err_tasklet_kill:
	tasklet_kill(&td->tasklet);
	iounmap(td->membase);
err_free_mem:
	kfree(td);
err_release_region:
	release_mem_region(iomem->start, resource_size(iomem));

	return err;

}