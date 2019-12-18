#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int min_heap_idx; } ;
struct event {TYPE_1__ ev_timeout_pos; } ;
struct TYPE_7__ {size_t n; struct event** p; } ;
typedef  TYPE_2__ min_heap_t ;

/* Variables and functions */
 int EV_SIZE_MAX ; 
 scalar_t__ min_heap_elem_greater (struct event*,struct event*) ; 
 int /*<<< orphan*/  min_heap_shift_down_ (TYPE_2__*,int,struct event*) ; 
 int /*<<< orphan*/  min_heap_shift_up_unconditional_ (TYPE_2__*,int,struct event*) ; 

int min_heap_erase_(min_heap_t* s, struct event* e)
{
	if (EV_SIZE_MAX != e->ev_timeout_pos.min_heap_idx)
	{
		struct event *last = s->p[--s->n];
		size_t parent = (e->ev_timeout_pos.min_heap_idx - 1) / 2;
		/* we replace e with the last element in the heap.  We might need to
		   shift it upward if it is less than its parent, or downward if it is
		   greater than one or both its children. Since the children are known
		   to be less than the parent, it can't need to shift both up and
		   down. */
		if (e->ev_timeout_pos.min_heap_idx > 0 && min_heap_elem_greater(s->p[parent], last))
			min_heap_shift_up_unconditional_(s, e->ev_timeout_pos.min_heap_idx, last);
		else
			min_heap_shift_down_(s, e->ev_timeout_pos.min_heap_idx, last);
		e->ev_timeout_pos.min_heap_idx = EV_SIZE_MAX;
		return 0;
	}
	return -1;
}