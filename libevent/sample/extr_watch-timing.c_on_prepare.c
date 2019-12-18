#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {long double tv_usec; scalar_t__ tv_sec; } ;
struct evwatch_prepare_cb_info {int dummy; } ;
struct evwatch {int dummy; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 TYPE_1__ check_time ; 
 int /*<<< orphan*/  durations ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (int /*<<< orphan*/ *,TYPE_1__*,struct timeval*) ; 
 int /*<<< orphan*/  evwatch_prepare_get_timeout (struct evwatch_prepare_cb_info const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expected ; 
 int /*<<< orphan*/  histogram_update (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  prepare_time ; 

__attribute__((used)) static void on_prepare(struct evwatch *watcher, const struct evwatch_prepare_cb_info *info, void *arg)
{
	struct timeval duration;
	evutil_gettimeofday(&prepare_time, NULL);
	evwatch_prepare_get_timeout(info, &expected);
	if (check_time.tv_sec != 0) {
		evutil_timersub(&prepare_time, &check_time, &duration);
		histogram_update(durations, duration.tv_sec + duration.tv_usec / 1000000.0l);
	}
}