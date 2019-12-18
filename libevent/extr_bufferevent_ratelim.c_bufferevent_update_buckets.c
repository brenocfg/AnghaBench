#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ev_base; } ;
struct bufferevent_private {TYPE_2__* rate_limiting; TYPE_1__ bev; } ;
struct TYPE_6__ {unsigned int last_updated; } ;
struct TYPE_5__ {int /*<<< orphan*/  cfg; TYPE_3__ limit; } ;

/* Variables and functions */
 unsigned int ev_token_bucket_get_tick_ (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_token_bucket_update_ (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  event_base_gettimeofday_cached (int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static inline void
bufferevent_update_buckets(struct bufferevent_private *bev)
{
	/* Must hold lock on bev. */
	struct timeval now;
	unsigned tick;
	event_base_gettimeofday_cached(bev->bev.ev_base, &now);
	tick = ev_token_bucket_get_tick_(&now, bev->rate_limiting->cfg);
	if (tick != bev->rate_limiting->limit.last_updated)
		ev_token_bucket_update_(&bev->rate_limiting->limit,
		    bev->rate_limiting->cfg, tick);
}