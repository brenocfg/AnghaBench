#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dmaengine_desc_callback {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct d40_desc {int is_in_client_list; int /*<<< orphan*/  node; TYPE_1__ txd; int /*<<< orphan*/  cyclic; } ;
struct d40_chan {scalar_t__ pending_tx; int /*<<< orphan*/  lock; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int DMA_PREP_INTERRUPT ; 
 scalar_t__ async_tx_test_ack (TYPE_1__*) ; 
 int /*<<< orphan*/  d40_desc_free (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_desc_remove (struct d40_desc*) ; 
 struct d40_desc* d40_first_active_get (struct d40_chan*) ; 
 struct d40_desc* d40_first_done (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_lcla_free_all (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  dma_cookie_complete (TYPE_1__*) ; 
 int /*<<< orphan*/  dmaengine_desc_callback_invoke (struct dmaengine_desc_callback*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback (TYPE_1__*,struct dmaengine_desc_callback*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_tasklet(unsigned long data)
{
	struct d40_chan *d40c = (struct d40_chan *) data;
	struct d40_desc *d40d;
	unsigned long flags;
	bool callback_active;
	struct dmaengine_desc_callback cb;

	spin_lock_irqsave(&d40c->lock, flags);

	/* Get first entry from the done list */
	d40d = d40_first_done(d40c);
	if (d40d == NULL) {
		/* Check if we have reached here for cyclic job */
		d40d = d40_first_active_get(d40c);
		if (d40d == NULL || !d40d->cyclic)
			goto check_pending_tx;
	}

	if (!d40d->cyclic)
		dma_cookie_complete(&d40d->txd);

	/*
	 * If terminating a channel pending_tx is set to zero.
	 * This prevents any finished active jobs to return to the client.
	 */
	if (d40c->pending_tx == 0) {
		spin_unlock_irqrestore(&d40c->lock, flags);
		return;
	}

	/* Callback to client */
	callback_active = !!(d40d->txd.flags & DMA_PREP_INTERRUPT);
	dmaengine_desc_get_callback(&d40d->txd, &cb);

	if (!d40d->cyclic) {
		if (async_tx_test_ack(&d40d->txd)) {
			d40_desc_remove(d40d);
			d40_desc_free(d40c, d40d);
		} else if (!d40d->is_in_client_list) {
			d40_desc_remove(d40d);
			d40_lcla_free_all(d40c, d40d);
			list_add_tail(&d40d->node, &d40c->client);
			d40d->is_in_client_list = true;
		}
	}

	d40c->pending_tx--;

	if (d40c->pending_tx)
		tasklet_schedule(&d40c->tasklet);

	spin_unlock_irqrestore(&d40c->lock, flags);

	if (callback_active)
		dmaengine_desc_callback_invoke(&cb, NULL);

	return;
 check_pending_tx:
	/* Rescue manouver if receiving double interrupts */
	if (d40c->pending_tx > 0)
		d40c->pending_tx--;
	spin_unlock_irqrestore(&d40c->lock, flags);
}