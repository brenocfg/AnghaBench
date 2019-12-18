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
struct event_base {int dummy; } ;
struct event {short ev_events; void* ev_arg; int /*<<< orphan*/  ev_callback; int /*<<< orphan*/  ev_fd; struct event_base* ev_base; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  event_callback_fn ;

/* Variables and functions */
 int /*<<< orphan*/  event_debug_assert_is_setup_ (struct event const*) ; 

void
event_get_assignment(const struct event *event, struct event_base **base_out, evutil_socket_t *fd_out, short *events_out, event_callback_fn *callback_out, void **arg_out)
{
	event_debug_assert_is_setup_(event);

	if (base_out)
		*base_out = event->ev_base;
	if (fd_out)
		*fd_out = event->ev_fd;
	if (events_out)
		*events_out = event->ev_events;
	if (callback_out)
		*callback_out = event->ev_callback;
	if (arg_out)
		*arg_out = event->ev_arg;
}