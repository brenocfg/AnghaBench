#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int min_heap_idx; } ;
struct event {TYPE_1__ ev_timeout_pos; } ;
struct TYPE_8__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ min_heap_t ;

/* Variables and functions */
 int EV_SIZE_MAX ; 
 scalar_t__ min_heap_elem_greater (int /*<<< orphan*/ ,struct event*) ; 
 int min_heap_push_ (TYPE_2__*,struct event*) ; 
 int /*<<< orphan*/  min_heap_shift_down_ (TYPE_2__*,int,struct event*) ; 
 int /*<<< orphan*/  min_heap_shift_up_unconditional_ (TYPE_2__*,int,struct event*) ; 

int min_heap_adjust_(min_heap_t *s, struct event *e)
{
	if (EV_SIZE_MAX == e->ev_timeout_pos.min_heap_idx) {
		return min_heap_push_(s, e);
	} else {
		size_t parent = (e->ev_timeout_pos.min_heap_idx - 1) / 2;
		/* The position of e has changed; we shift it up or down
		 * as needed.  We can't need to do both. */
		if (e->ev_timeout_pos.min_heap_idx > 0 && min_heap_elem_greater(s->p[parent], e))
			min_heap_shift_up_unconditional_(s, e->ev_timeout_pos.min_heap_idx, e);
		else
			min_heap_shift_down_(s, e->ev_timeout_pos.min_heap_idx, e);
		return 0;
	}
}