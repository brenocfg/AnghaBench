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
struct event {int dummy; } ;

/* Variables and functions */
 int event_add (struct event*,struct timeval const*) ; 
 int /*<<< orphan*/  evutil_timerisset (struct timeval const*) ; 

int
bufferevent_add_event_(struct event *ev, const struct timeval *tv)
{
	if (!evutil_timerisset(tv))
		return event_add(ev, NULL);
	else
		return event_add(ev, tv);
}