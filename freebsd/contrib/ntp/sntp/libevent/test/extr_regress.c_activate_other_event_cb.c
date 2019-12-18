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
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  event_active_later_ (struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_activate_other_event_cb ; 

__attribute__((used)) static void
activate_other_event_cb(evutil_socket_t fd, short what, void *other_)
{
	struct event *ev_activate = other_;
	++n_activate_other_event_cb;
	event_active_later_(ev_activate, EV_READ);
}