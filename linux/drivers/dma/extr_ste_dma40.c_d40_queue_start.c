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
struct d40_desc {int dummy; } ;
struct d40_chan {int busy; TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  d40_desc_load (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_desc_remove (struct d40_desc*) ; 
 int /*<<< orphan*/  d40_desc_submit (struct d40_chan*,struct d40_desc*) ; 
 struct d40_desc* d40_first_queued (struct d40_chan*) ; 
 int d40_start (struct d40_chan*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct d40_desc *d40_queue_start(struct d40_chan *d40c)
{
	struct d40_desc *d40d;
	int err;

	/* Start queued jobs, if any */
	d40d = d40_first_queued(d40c);

	if (d40d != NULL) {
		if (!d40c->busy) {
			d40c->busy = true;
			pm_runtime_get_sync(d40c->base->dev);
		}

		/* Remove from queue */
		d40_desc_remove(d40d);

		/* Add to active queue */
		d40_desc_submit(d40c, d40d);

		/* Initiate DMA job */
		d40_desc_load(d40c, d40d);

		/* Start dma job */
		err = d40_start(d40c);

		if (err)
			return NULL;
	}

	return d40d;
}