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
struct event {int /*<<< orphan*/  ev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLIST_INIT ; 
 int /*<<< orphan*/  event_debug_assert_not_added_ (struct event*) ; 
 int /*<<< orphan*/  event_debug_note_teardown_ (struct event*) ; 

void
event_debug_unassign(struct event *ev)
{
	event_debug_assert_not_added_(ev);
	event_debug_note_teardown_(ev);

	ev->ev_flags &= ~EVLIST_INIT;
}