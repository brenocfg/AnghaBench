#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zx_dma_phy {int /*<<< orphan*/ * ds_done; int /*<<< orphan*/ * ds_run; int /*<<< orphan*/ * vchan; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct zx_dma_dev {int /*<<< orphan*/  lock; TYPE_1__ slave; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct zx_dma_chan {TYPE_2__ vc; struct zx_dma_phy* phy; int /*<<< orphan*/  node; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct zx_dma_chan* to_zx_chan (struct dma_chan*) ; 
 struct zx_dma_dev* to_zx_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zx_dma_terminate_chan (struct zx_dma_phy*,struct zx_dma_dev*) ; 

__attribute__((used)) static int zx_dma_terminate_all(struct dma_chan *chan)
{
	struct zx_dma_chan *c = to_zx_chan(chan);
	struct zx_dma_dev *d = to_zx_dma(chan->device);
	struct zx_dma_phy *p = c->phy;
	unsigned long flags;
	LIST_HEAD(head);

	dev_dbg(d->slave.dev, "vchan %p: terminate all\n", &c->vc);

	/* Prevent this channel being scheduled */
	spin_lock(&d->lock);
	list_del_init(&c->node);
	spin_unlock(&d->lock);

	/* Clear the tx descriptor lists */
	spin_lock_irqsave(&c->vc.lock, flags);
	vchan_get_all_descriptors(&c->vc, &head);
	if (p) {
		/* vchan is assigned to a pchan - stop the channel */
		zx_dma_terminate_chan(p, d);
		c->phy = NULL;
		p->vchan = NULL;
		p->ds_run = NULL;
		p->ds_done = NULL;
	}
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_free_list(&c->vc, &head);

	return 0;
}