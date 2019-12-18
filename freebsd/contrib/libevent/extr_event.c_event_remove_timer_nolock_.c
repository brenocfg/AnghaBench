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
struct event_base {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ev_timeout; } ;
struct TYPE_4__ {TYPE_1__ ev_io; } ;
struct event {int ev_flags; TYPE_2__ ev_; struct event_base* ev_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_ASSERT_LOCKED (struct event_base*) ; 
 int EVLIST_TIMEOUT ; 
 int /*<<< orphan*/  event_debug (char*) ; 
 int /*<<< orphan*/  event_debug_assert_is_setup_ (struct event*) ; 
 int /*<<< orphan*/  event_queue_remove_timeout (struct event_base*,struct event*) ; 
 int /*<<< orphan*/  evutil_timerclear (int /*<<< orphan*/ *) ; 

int
event_remove_timer_nolock_(struct event *ev)
{
	struct event_base *base = ev->ev_base;

	EVENT_BASE_ASSERT_LOCKED(base);
	event_debug_assert_is_setup_(ev);

	event_debug(("event_remove_timer_nolock: event: %p", ev));

	/* If it's not pending on a timeout, we don't need to do anything. */
	if (ev->ev_flags & EVLIST_TIMEOUT) {
		event_queue_remove_timeout(base, ev);
		evutil_timerclear(&ev->ev_.ev_io.ev_timeout);
	}

	return (0);
}