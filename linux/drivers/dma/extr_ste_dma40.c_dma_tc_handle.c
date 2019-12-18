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
struct d40_desc {scalar_t__ lli_current; scalar_t__ lli_len; scalar_t__ cyclic; } ;
struct d40_chan {int busy; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  pending_tx; TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  d40_desc_done (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_desc_load (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_desc_remove (struct d40_desc*) ; 
 struct d40_desc* d40_first_active_get (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_lcla_free_all (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/ * d40_queue_start (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_residue (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_start (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_tx_is_linked (struct d40_chan*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_tc_handle(struct d40_chan *d40c)
{
	struct d40_desc *d40d;

	/* Get first active entry from list */
	d40d = d40_first_active_get(d40c);

	if (d40d == NULL)
		return;

	if (d40d->cyclic) {
		/*
		 * If this was a paritially loaded list, we need to reloaded
		 * it, and only when the list is completed.  We need to check
		 * for done because the interrupt will hit for every link, and
		 * not just the last one.
		 */
		if (d40d->lli_current < d40d->lli_len
		    && !d40_tx_is_linked(d40c)
		    && !d40_residue(d40c)) {
			d40_lcla_free_all(d40c, d40d);
			d40_desc_load(d40c, d40d);
			(void) d40_start(d40c);

			if (d40d->lli_current == d40d->lli_len)
				d40d->lli_current = 0;
		}
	} else {
		d40_lcla_free_all(d40c, d40d);

		if (d40d->lli_current < d40d->lli_len) {
			d40_desc_load(d40c, d40d);
			/* Start dma job */
			(void) d40_start(d40c);
			return;
		}

		if (d40_queue_start(d40c) == NULL) {
			d40c->busy = false;

			pm_runtime_mark_last_busy(d40c->base->dev);
			pm_runtime_put_autosuspend(d40c->base->dev);
		}

		d40_desc_remove(d40d);
		d40_desc_done(d40c, d40d);
	}

	d40c->pending_tx++;
	tasklet_schedule(&d40c->tasklet);

}