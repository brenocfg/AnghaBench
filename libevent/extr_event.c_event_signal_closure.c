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
struct event_base {int event_break; } ;
struct event {short ev_ncalls; short* ev_pncalls; int /*<<< orphan*/  ev_arg; int /*<<< orphan*/  ev_res; int /*<<< orphan*/  ev_fd; int /*<<< orphan*/  (* ev_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  th_base_lock ; 

__attribute__((used)) static inline void
event_signal_closure(struct event_base *base, struct event *ev)
{
	short ncalls;
	int should_break;

	/* Allows deletes to work */
	ncalls = ev->ev_ncalls;
	if (ncalls != 0)
		ev->ev_pncalls = &ncalls;
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	while (ncalls) {
		ncalls--;
		ev->ev_ncalls = ncalls;
		if (ncalls == 0)
			ev->ev_pncalls = NULL;
		(*ev->ev_callback)(ev->ev_fd, ev->ev_res, ev->ev_arg);

		EVBASE_ACQUIRE_LOCK(base, th_base_lock);
		should_break = base->event_break;
		EVBASE_RELEASE_LOCK(base, th_base_lock);

		if (should_break) {
			if (ncalls != 0)
				ev->ev_pncalls = NULL;
			return;
		}
	}
}