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
struct bufferevent {int /*<<< orphan*/  ev_write; int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_read; int /*<<< orphan*/  timeout_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 scalar_t__ bufferevent_add_event_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ event_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_remove_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ evutil_timerisset (int /*<<< orphan*/ *) ; 

int
bufferevent_generic_adj_existing_timeouts_(struct bufferevent *bev)
{
	int r = 0;
	if (event_pending(&bev->ev_read, EV_READ, NULL)) {
		if (evutil_timerisset(&bev->timeout_read)) {
			    if (bufferevent_add_event_(&bev->ev_read, &bev->timeout_read) < 0)
				    r = -1;
		} else {
			event_remove_timer(&bev->ev_read);
		}
	}
	if (event_pending(&bev->ev_write, EV_WRITE, NULL)) {
		if (evutil_timerisset(&bev->timeout_write)) {
			if (bufferevent_add_event_(&bev->ev_write, &bev->timeout_write) < 0)
				r = -1;
		} else {
			event_remove_timer(&bev->ev_write);
		}
	}
	return r;
}