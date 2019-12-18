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
struct timeval {int tv_usec; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_TIMEOUT ; 
 int /*<<< orphan*/  event_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  event_assign (struct event*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  event_del (struct event*) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  global_base ; 
 int /*<<< orphan*/  periodic_timeout_cb ; 

__attribute__((used)) static void
test_persistent_timeout(void)
{
	struct timeval tv;
	struct event ev;
	int count = 0;

	evutil_timerclear(&tv);
	tv.tv_usec = 10000;

	event_assign(&ev, global_base, -1, EV_TIMEOUT|EV_PERSIST,
	    periodic_timeout_cb, &count);
	event_add(&ev, &tv);

	event_dispatch();

	event_del(&ev);
}