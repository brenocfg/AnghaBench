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
typedef  int u32 ;
struct idma64_desc {scalar_t__ status; int /*<<< orphan*/  vdesc; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct idma64_chan {TYPE_1__ vchan; struct idma64_desc* desc; int /*<<< orphan*/  mask; } ;
struct idma64 {struct idma64_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_COMPLETE ; 
 scalar_t__ DMA_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  XFER ; 
 int /*<<< orphan*/  dma_writel (struct idma64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idma64_start_transfer (struct idma64_chan*) ; 
 int /*<<< orphan*/  idma64_stop_transfer (struct idma64_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idma64_chan_irq(struct idma64 *idma64, unsigned short c,
		u32 status_err, u32 status_xfer)
{
	struct idma64_chan *idma64c = &idma64->chan[c];
	struct idma64_desc *desc;

	spin_lock(&idma64c->vchan.lock);
	desc = idma64c->desc;
	if (desc) {
		if (status_err & (1 << c)) {
			dma_writel(idma64, CLEAR(ERROR), idma64c->mask);
			desc->status = DMA_ERROR;
		} else if (status_xfer & (1 << c)) {
			dma_writel(idma64, CLEAR(XFER), idma64c->mask);
			desc->status = DMA_COMPLETE;
			vchan_cookie_complete(&desc->vdesc);
			idma64_start_transfer(idma64c);
		}

		/* idma64_start_transfer() updates idma64c->desc */
		if (idma64c->desc == NULL || desc->status == DMA_ERROR)
			idma64_stop_transfer(idma64c);
	}
	spin_unlock(&idma64c->vchan.lock);
}