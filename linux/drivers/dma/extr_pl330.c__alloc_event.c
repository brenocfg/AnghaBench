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
struct pl330_thread {int id; struct pl330_dmac* dmac; } ;
struct TYPE_2__ {int num_events; } ;
struct pl330_dmac {int* events; TYPE_1__ pcfg; } ;

/* Variables and functions */

__attribute__((used)) static inline int _alloc_event(struct pl330_thread *thrd)
{
	struct pl330_dmac *pl330 = thrd->dmac;
	int ev;

	for (ev = 0; ev < pl330->pcfg.num_events; ev++)
		if (pl330->events[ev] == -1) {
			pl330->events[ev] = thrd->id;
			return ev;
		}

	return -1;
}