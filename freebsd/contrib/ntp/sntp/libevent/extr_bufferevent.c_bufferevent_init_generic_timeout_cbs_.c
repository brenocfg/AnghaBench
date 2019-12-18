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
struct bufferevent {int /*<<< orphan*/  ev_base; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_FINALIZE ; 
 int /*<<< orphan*/  bufferevent_generic_read_timeout_cb ; 
 int /*<<< orphan*/  bufferevent_generic_write_timeout_cb ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 

void
bufferevent_init_generic_timeout_cbs_(struct bufferevent *bev)
{
	event_assign(&bev->ev_read, bev->ev_base, -1, EV_FINALIZE,
	    bufferevent_generic_read_timeout_cb, bev);
	event_assign(&bev->ev_write, bev->ev_base, -1, EV_FINALIZE,
	    bufferevent_generic_write_timeout_cb, bev);
}