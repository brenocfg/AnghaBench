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
struct event {int ev_flags; int ev_pri; TYPE_1__* ev_base; } ;
struct TYPE_2__ {int nactivequeues; } ;

/* Variables and functions */
 int EVLIST_ACTIVE ; 
 int /*<<< orphan*/  event_debug_assert_is_setup_ (struct event*) ; 

int
event_priority_set(struct event *ev, int pri)
{
	event_debug_assert_is_setup_(ev);

	if (ev->ev_flags & EVLIST_ACTIVE)
		return (-1);
	if (pri < 0 || pri >= ev->ev_base->nactivequeues)
		return (-1);

	ev->ev_pri = pri;

	return (0);
}