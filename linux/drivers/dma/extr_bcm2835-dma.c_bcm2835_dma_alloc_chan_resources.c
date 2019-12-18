#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;
struct bcm2835_dma_cb {int dummy; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ chan; } ;
struct bcm2835_chan {int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq_number; int /*<<< orphan*/  cb_pool; int /*<<< orphan*/  ch; TYPE_3__ vc; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  bcm2835_dma_callback ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dma_pool_create (int /*<<< orphan*/ ,struct device*,int,int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct bcm2835_chan*) ; 
 struct bcm2835_chan* to_bcm2835_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int bcm2835_dma_alloc_chan_resources(struct dma_chan *chan)
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);
	struct device *dev = c->vc.chan.device->dev;

	dev_dbg(dev, "Allocating DMA channel %d\n", c->ch);

	/*
	 * Control blocks are 256 bit in length and must start at a 256 bit
	 * (32 byte) aligned address (BCM2835 ARM Peripherals, sec. 4.2.1.1).
	 */
	c->cb_pool = dma_pool_create(dev_name(dev), dev,
				     sizeof(struct bcm2835_dma_cb), 32, 0);
	if (!c->cb_pool) {
		dev_err(dev, "unable to allocate descriptor pool\n");
		return -ENOMEM;
	}

	return request_irq(c->irq_number, bcm2835_dma_callback,
			   c->irq_flags, "DMA IRQ", c);
}