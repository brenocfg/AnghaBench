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
struct timeval {int dummy; } ;
struct event {int ev_flags; int ev_events; int ev_res; int /*<<< orphan*/  ev_timeout; } ;

/* Variables and functions */
 int EVLIST_ACTIVE ; 
 int EVLIST_INSERTED ; 
 int EVLIST_SIGNAL ; 
 int EVLIST_TIMEOUT ; 
 int EV_READ ; 
 int EV_SIGNAL ; 
 int EV_TIMEOUT ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  gettime (struct timeval*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeradd (struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,struct timeval*,struct timeval*) ; 

int
event_pending(struct event *ev, short event, struct timeval *tv)
{
	struct timeval	now, res;
	int flags = 0;

	if (ev->ev_flags & EVLIST_INSERTED)
		flags |= (ev->ev_events & (EV_READ|EV_WRITE));
	if (ev->ev_flags & EVLIST_ACTIVE)
		flags |= ev->ev_res;
	if (ev->ev_flags & EVLIST_TIMEOUT)
		flags |= EV_TIMEOUT;
	if (ev->ev_flags & EVLIST_SIGNAL)
		flags |= EV_SIGNAL;

	event &= (EV_TIMEOUT|EV_READ|EV_WRITE|EV_SIGNAL);

	/* See if there is a timeout that we should report */
	if (tv != NULL && (flags & event & EV_TIMEOUT)) {
		gettime(&now);
		timersub(&ev->ev_timeout, &now, &res);
		/* correctly remap to real time */
		gettimeofday(&now, NULL);
		timeradd(&now, &res, tv);
	}

	return (flags & event);
}