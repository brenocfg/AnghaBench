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
struct timeval {int dummy; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct event_base {int /*<<< orphan*/  tv_clock_diff; TYPE_1__ tv_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 struct event_base* current_base ; 
 int evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timeradd (TYPE_1__*,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  th_base_lock ; 

int
event_base_gettimeofday_cached(struct event_base *base, struct timeval *tv)
{
	int r;
	if (!base) {
		base = current_base;
		if (!current_base)
			return evutil_gettimeofday(tv, NULL);
	}

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	if (base->tv_cache.tv_sec == 0) {
		r = evutil_gettimeofday(tv, NULL);
	} else {
		evutil_timeradd(&base->tv_cache, &base->tv_clock_diff, tv);
		r = 0;
	}
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	return r;
}