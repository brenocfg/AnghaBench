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
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct event_base {int flags; TYPE_1__ tv_cache; } ;

/* Variables and functions */
 int EVENT_BASE_FLAG_NO_CACHE_TIME ; 
 int /*<<< orphan*/  gettime (struct event_base*,TYPE_1__*) ; 

__attribute__((used)) static inline void
update_time_cache(struct event_base *base)
{
	base->tv_cache.tv_sec = 0;
	if (!(base->flags & EVENT_BASE_FLAG_NO_CACHE_TIME))
	    gettime(base, &base->tv_cache);
}