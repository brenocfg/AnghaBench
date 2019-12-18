#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int min_heap_idx; } ;
struct event {TYPE_1__ ev_timeout_pos; } ;
struct TYPE_6__ {int n; struct event** p; } ;
typedef  TYPE_2__ min_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  min_heap_shift_down_ (TYPE_2__*,unsigned int,struct event*) ; 

struct event* min_heap_pop_(min_heap_t* s)
{
	if (s->n)
	{
		struct event* e = *s->p;
		min_heap_shift_down_(s, 0u, s->p[--s->n]);
		e->ev_timeout_pos.min_heap_idx = -1;
		return e;
	}
	return 0;
}