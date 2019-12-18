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
 int EVLIST_ACTIVE ; 
 int EVLIST_ACTIVE_LATER ; 
 int /*<<< orphan*/  event_queue_insert_active_later (struct event_base*,struct event_callback*) ; 
 int /*<<< orphan*/  evthread_notify_base (struct event_base*) ; 

void
event_callback_activate_later_nolock_(struct event_base *base,
    struct event_callback *evcb)
{
	if (evcb->evcb_flags & (EVLIST_ACTIVE|EVLIST_ACTIVE_LATER))
		return;

	event_queue_insert_active_later(base, evcb);
	if (EVBASE_NEED_NOTIFY(base))
		evthread_notify_base(base);
}