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
struct omap_dmadev {int /*<<< orphan*/  irq_lock; } ;
struct omap_chan {int paused; TYPE_1__* desc; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  clnk_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLNK_CTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  omap_dma_chan_write (struct omap_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dma_start (struct omap_chan*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct omap_chan* to_omap_dma_chan (struct dma_chan*) ; 
 struct omap_dmadev* to_omap_dma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_dma_resume(struct dma_chan *chan)
{
	struct omap_chan *c = to_omap_dma_chan(chan);
	struct omap_dmadev *od = to_omap_dma_dev(chan->device);
	unsigned long flags;
	int ret = -EINVAL;

	spin_lock_irqsave(&od->irq_lock, flags);

	if (c->paused && c->desc) {
		mb();

		/* Restore channel link register */
		omap_dma_chan_write(c, CLNK_CTRL, c->desc->clnk_ctrl);

		omap_dma_start(c, c->desc);
		c->paused = false;
		ret = 0;
	}
	spin_unlock_irqrestore(&od->irq_lock, flags);

	return ret;
}