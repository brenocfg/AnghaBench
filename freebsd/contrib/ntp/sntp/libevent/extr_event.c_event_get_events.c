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
struct event {short ev_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_debug_assert_is_setup_ (struct event const*) ; 

short
event_get_events(const struct event *ev)
{
	event_debug_assert_is_setup_(ev);
	return ev->ev_events;
}