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
struct event_callback {int evcb_flags; size_t evcb_pri; scalar_t__ evcb_closure; } ;
struct event_base {size_t nactivequeues; int n_deferreds_queued; int /*<<< orphan*/ * activequeues; int /*<<< orphan*/  active_later_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_ASSERT_LOCKED (struct event_base*) ; 
 int EVLIST_ACTIVE ; 
 int EVLIST_ACTIVE_LATER ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ EV_CLOSURE_CB_SELF ; 
 struct event_callback* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct event_callback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct event_callback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evcb_active_next ; 

__attribute__((used)) static void
event_queue_make_later_events_active(struct event_base *base)
{
	struct event_callback *evcb;
	EVENT_BASE_ASSERT_LOCKED(base);

	while ((evcb = TAILQ_FIRST(&base->active_later_queue))) {
		TAILQ_REMOVE(&base->active_later_queue, evcb, evcb_active_next);
		evcb->evcb_flags = (evcb->evcb_flags & ~EVLIST_ACTIVE_LATER) | EVLIST_ACTIVE;
		EVUTIL_ASSERT(evcb->evcb_pri < base->nactivequeues);
		TAILQ_INSERT_TAIL(&base->activequeues[evcb->evcb_pri], evcb, evcb_active_next);
		base->n_deferreds_queued += (evcb->evcb_closure == EV_CLOSURE_CB_SELF);
	}
}