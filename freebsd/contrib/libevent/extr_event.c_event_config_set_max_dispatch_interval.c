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
struct TYPE_2__ {int tv_sec; } ;
struct event_config {int max_dispatch_callbacks; int limit_callbacks_after_prio; TYPE_1__ max_dispatch_interval; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct timeval const*,int) ; 

int
event_config_set_max_dispatch_interval(struct event_config *cfg,
    const struct timeval *max_interval, int max_callbacks, int min_priority)
{
	if (max_interval)
		memcpy(&cfg->max_dispatch_interval, max_interval,
		    sizeof(struct timeval));
	else
		cfg->max_dispatch_interval.tv_sec = -1;
	cfg->max_dispatch_callbacks =
	    max_callbacks >= 0 ? max_callbacks : INT_MAX;
	if (min_priority < 0)
		min_priority = 0;
	cfg->limit_callbacks_after_prio = min_priority;
	return (0);
}