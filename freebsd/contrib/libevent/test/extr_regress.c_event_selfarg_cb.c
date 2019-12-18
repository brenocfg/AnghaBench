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
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_assert_ok_ (struct event_base*) ; 
 struct event* event_base_get_running_event (struct event_base*) ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,int /*<<< orphan*/ *) ; 
 struct event_base* event_get_base (struct event*) ; 
 int /*<<< orphan*/  tt_want (int) ; 

__attribute__((used)) static void
event_selfarg_cb(evutil_socket_t fd, short event, void *arg)
{
	struct event *ev = arg;
	struct event_base *base = event_get_base(ev);
	event_base_assert_ok_(base);
	event_base_loopexit(base, NULL);
	tt_want(ev == event_base_get_running_event(base));
}