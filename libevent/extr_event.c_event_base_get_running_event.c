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
struct event_base {struct event_callback* current_event; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 scalar_t__ EVBASE_IN_THREAD (struct event_base*) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int EVLIST_INIT ; 
 struct event* event_callback_to_event (struct event_callback*) ; 
 int /*<<< orphan*/  th_base_lock ; 

struct event *
event_base_get_running_event(struct event_base *base)
{
	struct event *ev = NULL;
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	if (EVBASE_IN_THREAD(base)) {
		struct event_callback *evcb = base->current_event;
		if (evcb->evcb_flags & EVLIST_INIT)
			ev = event_callback_to_event(evcb);
	}
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	return ev;
}