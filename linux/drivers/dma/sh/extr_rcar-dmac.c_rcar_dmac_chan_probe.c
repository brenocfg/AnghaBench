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
struct TYPE_3__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  done; int /*<<< orphan*/  active; int /*<<< orphan*/  pending; int /*<<< orphan*/  free; } ;
struct dma_chan {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct rcar_dmac_chan {unsigned int index; int /*<<< orphan*/  irq; TYPE_1__ desc; int /*<<< orphan*/  lock; int /*<<< orphan*/  mid_rid; scalar_t__ iomem; struct dma_chan chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  channels; } ;
struct rcar_dmac {int /*<<< orphan*/  dev; TYPE_2__ engine; scalar_t__ iomem; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ RCAR_DMAC_CHAN_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rcar_dmac_chan*) ; 
 int /*<<< orphan*/  dma_cookie_init (struct dma_chan*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  rcar_dmac_isr_channel ; 
 int /*<<< orphan*/  rcar_dmac_isr_channel_thread ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_dmac_chan_probe(struct rcar_dmac *dmac,
				struct rcar_dmac_chan *rchan,
				unsigned int index)
{
	struct platform_device *pdev = to_platform_device(dmac->dev);
	struct dma_chan *chan = &rchan->chan;
	char pdev_irqname[5];
	char *irqname;
	int ret;

	rchan->index = index;
	rchan->iomem = dmac->iomem + RCAR_DMAC_CHAN_OFFSET(index);
	rchan->mid_rid = -EINVAL;

	spin_lock_init(&rchan->lock);

	INIT_LIST_HEAD(&rchan->desc.free);
	INIT_LIST_HEAD(&rchan->desc.pending);
	INIT_LIST_HEAD(&rchan->desc.active);
	INIT_LIST_HEAD(&rchan->desc.done);
	INIT_LIST_HEAD(&rchan->desc.wait);

	/* Request the channel interrupt. */
	sprintf(pdev_irqname, "ch%u", index);
	rchan->irq = platform_get_irq_byname(pdev, pdev_irqname);
	if (rchan->irq < 0)
		return -ENODEV;

	irqname = devm_kasprintf(dmac->dev, GFP_KERNEL, "%s:%u",
				 dev_name(dmac->dev), index);
	if (!irqname)
		return -ENOMEM;

	/*
	 * Initialize the DMA engine channel and add it to the DMA engine
	 * channels list.
	 */
	chan->device = &dmac->engine;
	dma_cookie_init(chan);

	list_add_tail(&chan->device_node, &dmac->engine.channels);

	ret = devm_request_threaded_irq(dmac->dev, rchan->irq,
					rcar_dmac_isr_channel,
					rcar_dmac_isr_channel_thread, 0,
					irqname, rchan);
	if (ret) {
		dev_err(dmac->dev, "failed to request IRQ %u (%d)\n",
			rchan->irq, ret);
		return ret;
	}

	return 0;
}