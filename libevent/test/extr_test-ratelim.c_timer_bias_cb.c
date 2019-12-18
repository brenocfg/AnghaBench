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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_del (struct event*) ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int timer_bias_events ; 
 int /*<<< orphan*/  timer_bias_spend ; 
 struct timeval timer_bias_start ; 

__attribute__((used)) static void
timer_bias_cb(evutil_socket_t fd, short events, void *arg)
{
	struct event *event = arg;
	struct timeval end;
	struct timeval diff;

	/** XXX: use rdtsc? (portability issues?) */
	evutil_gettimeofday(&end, NULL);
	evutil_timersub(&end, &timer_bias_start, &diff);
	timer_bias_spend += diff.tv_sec + diff.tv_usec * 1e6;
	timer_bias_start = end;

	if (++timer_bias_events == 100)
		event_del(event);
}