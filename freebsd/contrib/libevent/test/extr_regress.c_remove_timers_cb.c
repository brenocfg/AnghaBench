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
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_remove_timer (struct event*) ; 

__attribute__((used)) static void remove_timers_cb(evutil_socket_t fd, short what, void *arg)
{
	struct event **ep = arg;
	(void) fd; (void) what;
	event_remove_timer(ep[0]);
	event_remove_timer(ep[1]);
}