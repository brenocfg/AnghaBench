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
struct timeval {scalar_t__ tv_sec; long double tv_usec; } ;
struct evwatch_check_cb_info {int dummy; } ;
struct evwatch {int dummy; } ;

/* Variables and functions */
 struct timeval check_time ; 
 int /*<<< orphan*/  delays ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  expected ; 
 int /*<<< orphan*/  histogram_update (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  prepare_time ; 

__attribute__((used)) static void on_check(struct evwatch *watcher, const struct evwatch_check_cb_info *info, void *arg)
{
	struct timeval actual, delay;
	evutil_gettimeofday(&check_time, NULL);
	evutil_timersub(&check_time, &prepare_time, &actual);
	evutil_timersub(&actual, &expected, &delay);
	if (delay.tv_sec >= 0)
		histogram_update(delays, delay.tv_sec + delay.tv_usec / 1000000.0l);
}