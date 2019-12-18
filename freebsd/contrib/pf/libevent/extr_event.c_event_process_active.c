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
struct event_list {int dummy; } ;
struct event_base {int nactivequeues; struct event_list** activequeues; int /*<<< orphan*/  event_count_active; } ;
struct event {short ev_ncalls; short* ev_pncalls; int /*<<< orphan*/  ev_arg; int /*<<< orphan*/  ev_res; scalar_t__ ev_fd; int /*<<< orphan*/  (* ev_callback ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVLIST_ACTIVE ; 
 struct event* TAILQ_FIRST (struct event_list*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ event_gotsig ; 
 int /*<<< orphan*/  event_queue_remove (struct event_base*,struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
event_process_active(struct event_base *base)
{
	struct event *ev;
	struct event_list *activeq = NULL;
	int i;
	short ncalls;

	if (!base->event_count_active)
		return;

	for (i = 0; i < base->nactivequeues; ++i) {
		if (TAILQ_FIRST(base->activequeues[i]) != NULL) {
			activeq = base->activequeues[i];
			break;
		}
	}

	assert(activeq != NULL);

	for (ev = TAILQ_FIRST(activeq); ev; ev = TAILQ_FIRST(activeq)) {
		event_queue_remove(base, ev, EVLIST_ACTIVE);
		
		/* Allows deletes to work */
		ncalls = ev->ev_ncalls;
		ev->ev_pncalls = &ncalls;
		while (ncalls) {
			ncalls--;
			ev->ev_ncalls = ncalls;
			(*ev->ev_callback)((int)ev->ev_fd, ev->ev_res, ev->ev_arg);
			if (event_gotsig)
				return;
		}
	}
}