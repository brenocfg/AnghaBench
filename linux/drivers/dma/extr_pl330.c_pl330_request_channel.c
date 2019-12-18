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
struct pl330_thread {int free; scalar_t__ ev; int lstenq; int req_running; TYPE_2__* req; } ;
struct TYPE_3__ {int num_chan; } ;
struct pl330_dmac {scalar_t__ state; struct pl330_thread* channels; TYPE_1__ pcfg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 scalar_t__ DYING ; 
 scalar_t__ _alloc_event (struct pl330_thread*) ; 
 scalar_t__ _chan_ns (struct pl330_dmac*,int) ; 
 int /*<<< orphan*/  _manager_ns (struct pl330_thread*) ; 

__attribute__((used)) static struct pl330_thread *pl330_request_channel(struct pl330_dmac *pl330)
{
	struct pl330_thread *thrd = NULL;
	int chans, i;

	if (pl330->state == DYING)
		return NULL;

	chans = pl330->pcfg.num_chan;

	for (i = 0; i < chans; i++) {
		thrd = &pl330->channels[i];
		if ((thrd->free) && (!_manager_ns(thrd) ||
					_chan_ns(pl330, i))) {
			thrd->ev = _alloc_event(thrd);
			if (thrd->ev >= 0) {
				thrd->free = false;
				thrd->lstenq = 1;
				thrd->req[0].desc = NULL;
				thrd->req[1].desc = NULL;
				thrd->req_running = -1;
				break;
			}
		}
		thrd = NULL;
	}

	return thrd;
}