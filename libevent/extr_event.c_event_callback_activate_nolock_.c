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
struct event_callback {int evcb_flags; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 scalar_t__ EVBASE_NEED_NOTIFY (struct event_base*) ; 
#define  EVLIST_ACTIVE 129 
#define  EVLIST_ACTIVE_LATER 128 
 int EVLIST_FINALIZING ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVUTIL_FALLTHROUGH ; 
 int /*<<< orphan*/  event_queue_insert_active (struct event_base*,struct event_callback*) ; 
 int /*<<< orphan*/  event_queue_remove_active_later (struct event_base*,struct event_callback*) ; 
 int /*<<< orphan*/  evthread_notify_base (struct event_base*) ; 

int
event_callback_activate_nolock_(struct event_base *base,
    struct event_callback *evcb)
{
	int r = 1;

	if (evcb->evcb_flags & EVLIST_FINALIZING)
		return 0;

	switch (evcb->evcb_flags & (EVLIST_ACTIVE|EVLIST_ACTIVE_LATER)) {
	default:
		EVUTIL_ASSERT(0);
		EVUTIL_FALLTHROUGH;
	case EVLIST_ACTIVE_LATER:
		event_queue_remove_active_later(base, evcb);
		r = 0;
		break;
	case EVLIST_ACTIVE:
		return 0;
	case 0:
		break;
	}

	event_queue_insert_active(base, evcb);

	if (EVBASE_NEED_NOTIFY(base))
		evthread_notify_base(base);

	return r;
}