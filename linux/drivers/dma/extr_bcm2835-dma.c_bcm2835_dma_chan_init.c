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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct bcm2835_dmadev {int /*<<< orphan*/  base; TYPE_2__ ddev; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc_free; } ;
struct bcm2835_chan {int ch; int irq_number; unsigned int irq_flags; int is_lite_channel; scalar_t__ chan_base; TYPE_1__ vc; } ;

/* Variables and functions */
 scalar_t__ BCM2835_DMA_CHANIO (int /*<<< orphan*/ ,int) ; 
 scalar_t__ BCM2835_DMA_DEBUG ; 
 int BCM2835_DMA_DEBUG_LITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm2835_dma_desc_free ; 
 struct bcm2835_chan* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int bcm2835_dma_chan_init(struct bcm2835_dmadev *d, int chan_id,
				 int irq, unsigned int irq_flags)
{
	struct bcm2835_chan *c;

	c = devm_kzalloc(d->ddev.dev, sizeof(*c), GFP_KERNEL);
	if (!c)
		return -ENOMEM;

	c->vc.desc_free = bcm2835_dma_desc_free;
	vchan_init(&c->vc, &d->ddev);

	c->chan_base = BCM2835_DMA_CHANIO(d->base, chan_id);
	c->ch = chan_id;
	c->irq_number = irq;
	c->irq_flags = irq_flags;

	/* check in DEBUG register if this is a LITE channel */
	if (readl(c->chan_base + BCM2835_DMA_DEBUG) &
		BCM2835_DMA_DEBUG_LITE)
		c->is_lite_channel = true;

	return 0;
}