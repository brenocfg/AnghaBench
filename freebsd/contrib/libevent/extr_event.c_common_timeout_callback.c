#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct event_base {int dummy; } ;
struct TYPE_2__ {scalar_t__ tv_sec; int tv_usec; } ;
struct event {TYPE_1__ ev_timeout; } ;
struct common_timeout_list {int /*<<< orphan*/  events; struct event_base* base; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_DEL_NOBLOCK ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int MICROSECONDS_MASK ; 
 struct event* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_timeout_schedule (struct common_timeout_list*,struct timeval*,struct event*) ; 
 int /*<<< orphan*/  event_active_nolock_ (struct event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_del_nolock_ (struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettime (struct event_base*,struct timeval*) ; 
 int /*<<< orphan*/  th_base_lock ; 

__attribute__((used)) static void
common_timeout_callback(evutil_socket_t fd, short what, void *arg)
{
	struct timeval now;
	struct common_timeout_list *ctl = arg;
	struct event_base *base = ctl->base;
	struct event *ev = NULL;
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	gettime(base, &now);
	while (1) {
		ev = TAILQ_FIRST(&ctl->events);
		if (!ev || ev->ev_timeout.tv_sec > now.tv_sec ||
		    (ev->ev_timeout.tv_sec == now.tv_sec &&
			(ev->ev_timeout.tv_usec&MICROSECONDS_MASK) > now.tv_usec))
			break;
		event_del_nolock_(ev, EVENT_DEL_NOBLOCK);
		event_active_nolock_(ev, EV_TIMEOUT, 1);
	}
	if (ev)
		common_timeout_schedule(ctl, &now, ev);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}