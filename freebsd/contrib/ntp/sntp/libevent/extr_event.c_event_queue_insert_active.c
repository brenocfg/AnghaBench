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
struct event_callback {int evcb_flags; size_t evcb_pri; } ;
struct event_base {size_t nactivequeues; int /*<<< orphan*/ * activequeues; int /*<<< orphan*/  event_count_active; int /*<<< orphan*/  event_count_active_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_ASSERT_LOCKED (struct event_base*) ; 
 int EVLIST_ACTIVE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  INCR_EVENT_COUNT (struct event_base*,int) ; 
 int /*<<< orphan*/  MAX_EVENT_COUNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct event_callback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evcb_active_next ; 

__attribute__((used)) static void
event_queue_insert_active(struct event_base *base, struct event_callback *evcb)
{
	EVENT_BASE_ASSERT_LOCKED(base);

	if (evcb->evcb_flags & EVLIST_ACTIVE) {
		/* Double insertion is possible for active events */
		return;
	}

	INCR_EVENT_COUNT(base, evcb->evcb_flags);

	evcb->evcb_flags |= EVLIST_ACTIVE;

	base->event_count_active++;
	MAX_EVENT_COUNT(base->event_count_active_max, base->event_count_active);
	EVUTIL_ASSERT(evcb->evcb_pri < base->nactivequeues);
	TAILQ_INSERT_TAIL(&base->activequeues[evcb->evcb_pri],
	    evcb, evcb_active_next);
}