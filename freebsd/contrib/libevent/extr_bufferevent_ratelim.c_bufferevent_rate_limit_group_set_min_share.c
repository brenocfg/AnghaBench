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
struct TYPE_2__ {size_t read_rate; size_t write_rate; } ;
struct bufferevent_rate_limit_group {size_t configured_min_share; size_t min_share; TYPE_1__ rate_limit_cfg; } ;

/* Variables and functions */
 size_t EV_SSIZE_MAX ; 

int
bufferevent_rate_limit_group_set_min_share(
	struct bufferevent_rate_limit_group *g,
	size_t share)
{
	if (share > EV_SSIZE_MAX)
		return -1;

	g->configured_min_share = share;

	/* Can't set share to less than the one-tick maximum.  IOW, at steady
	 * state, at least one connection can go per tick. */
	if (share > g->rate_limit_cfg.read_rate)
		share = g->rate_limit_cfg.read_rate;
	if (share > g->rate_limit_cfg.write_rate)
		share = g->rate_limit_cfg.write_rate;

	g->min_share = share;
	return 0;
}