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
struct virt_dma_desc {int /*<<< orphan*/  tx; int /*<<< orphan*/  node; } ;
struct bcm2835_desc {TYPE_1__* cb_list; } ;
struct bcm2835_chan {scalar_t__ chan_base; struct bcm2835_desc* desc; int /*<<< orphan*/  vc; } ;
struct TYPE_2__ {int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_DMA_ACTIVE ; 
 scalar_t__ BCM2835_DMA_ADDR ; 
 scalar_t__ BCM2835_DMA_CS ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct bcm2835_desc* to_bcm2835_dma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bcm2835_dma_start_desc(struct bcm2835_chan *c)
{
	struct virt_dma_desc *vd = vchan_next_desc(&c->vc);
	struct bcm2835_desc *d;

	if (!vd) {
		c->desc = NULL;
		return;
	}

	list_del(&vd->node);

	c->desc = d = to_bcm2835_dma_desc(&vd->tx);

	writel(d->cb_list[0].paddr, c->chan_base + BCM2835_DMA_ADDR);
	writel(BCM2835_DMA_ACTIVE, c->chan_base + BCM2835_DMA_CS);
}