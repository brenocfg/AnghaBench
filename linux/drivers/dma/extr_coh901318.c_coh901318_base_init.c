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
struct dma_device {int /*<<< orphan*/  channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct coh901318_chan {int id; TYPE_1__ chan; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  queue; int /*<<< orphan*/  active; int /*<<< orphan*/  free; scalar_t__ busy; scalar_t__ nbr_active_done; int /*<<< orphan*/  lock; struct coh901318_base* base; } ;
struct coh901318_base {struct coh901318_chan* chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_tasklet ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void coh901318_base_init(struct dma_device *dma, const int *pick_chans,
				struct coh901318_base *base)
{
	int chans_i;
	int i = 0;
	struct coh901318_chan *cohc;

	INIT_LIST_HEAD(&dma->channels);

	for (chans_i = 0; pick_chans[chans_i] != -1; chans_i += 2) {
		for (i = pick_chans[chans_i]; i <= pick_chans[chans_i+1]; i++) {
			cohc = &base->chans[i];

			cohc->base = base;
			cohc->chan.device = dma;
			cohc->id = i;

			/* TODO: do we really need this lock if only one
			 * client is connected to each channel?
			 */

			spin_lock_init(&cohc->lock);

			cohc->nbr_active_done = 0;
			cohc->busy = 0;
			INIT_LIST_HEAD(&cohc->free);
			INIT_LIST_HEAD(&cohc->active);
			INIT_LIST_HEAD(&cohc->queue);

			tasklet_init(&cohc->tasklet, dma_tasklet,
				     (unsigned long) cohc);

			list_add_tail(&cohc->chan.device_node,
				      &dma->channels);
		}
	}
}