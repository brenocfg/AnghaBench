#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct event_base {int dummy; } ;
struct event {int ev_flags; int ev_res; struct event_base* ev_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_ASSERT_LOCKED (struct event_base*) ; 
 int EVLIST_ACTIVE ; 
 int EVLIST_ACTIVE_LATER ; 
 int /*<<< orphan*/  event_callback_activate_later_nolock_ (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_to_event_callback (struct event*) ; 

void
event_active_later_nolock_(struct event *ev, int res)
{
	struct event_base *base = ev->ev_base;
	EVENT_BASE_ASSERT_LOCKED(base);

	if (ev->ev_flags & (EVLIST_ACTIVE|EVLIST_ACTIVE_LATER)) {
		/* We get different kinds of events, add them together */
		ev->ev_res |= res;
		return;
	}

	ev->ev_res = res;

	event_callback_activate_later_nolock_(base, event_to_event_callback(ev));
}