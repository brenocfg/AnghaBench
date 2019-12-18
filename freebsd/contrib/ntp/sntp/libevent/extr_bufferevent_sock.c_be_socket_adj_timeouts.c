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
 scalar_t__ be_socket_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ event_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_remove_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ evutil_timerisset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
be_socket_adj_timeouts(struct bufferevent *bufev)
{
	int r = 0;
	if (event_pending(&bufev->ev_read, EV_READ, NULL)) {
		if (evutil_timerisset(&bufev->timeout_read)) {
			    if (be_socket_add(&bufev->ev_read, &bufev->timeout_read) < 0)
				    r = -1;
		} else {
			event_remove_timer(&bufev->ev_read);
		}
	}
	if (event_pending(&bufev->ev_write, EV_WRITE, NULL)) {
		if (evutil_timerisset(&bufev->timeout_write)) {
			if (be_socket_add(&bufev->ev_write, &bufev->timeout_write) < 0)
				r = -1;
		} else {
			event_remove_timer(&bufev->ev_write);
		}
	}
	return r;
}