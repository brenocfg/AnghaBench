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
struct timeval {double tv_sec; double tv_usec; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  event_is_persistent ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  evutil_timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 struct timeval lasttime ; 
 int /*<<< orphan*/  printf (char*,int,double) ; 

__attribute__((used)) static void
timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct timeval newtime, difference;
	struct event *timeout = arg;
	double elapsed;

	evutil_gettimeofday(&newtime, NULL);
	evutil_timersub(&newtime, &lasttime, &difference);
	elapsed = difference.tv_sec +
	    (difference.tv_usec / 1.0e6);

	printf("timeout_cb called at %d: %.3f seconds elapsed.\n",
	    (int)newtime.tv_sec, elapsed);
	lasttime = newtime;

	if (! event_is_persistent) {
		struct timeval tv;
		evutil_timerclear(&tv);
		tv.tv_sec = 2;
		event_add(timeout, &tv);
	}
}