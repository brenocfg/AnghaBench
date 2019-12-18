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
struct TYPE_2__ {scalar_t__ read_limit; scalar_t__ write_limit; } ;
struct bufferevent_rate_limit_group {scalar_t__ min_share; TYPE_1__ rate_limit; scalar_t__ write_suspended; scalar_t__ pending_unsuspend_write; scalar_t__ read_suspended; scalar_t__ pending_unsuspend_read; int /*<<< orphan*/  rate_limit_cfg; int /*<<< orphan*/  master_refill_event; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  UNLOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  bev_group_unsuspend_reading_ (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  bev_group_unsuspend_writing_ (struct bufferevent_rate_limit_group*) ; 
 unsigned int ev_token_bucket_get_tick_ (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_token_bucket_update_ (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  event_base_gettimeofday_cached (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  event_get_base (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bev_group_refill_callback_(evutil_socket_t fd, short what, void *arg)
{
	struct bufferevent_rate_limit_group *g = arg;
	unsigned tick;
	struct timeval now;

	event_base_gettimeofday_cached(event_get_base(&g->master_refill_event), &now);

	LOCK_GROUP(g);

	tick = ev_token_bucket_get_tick_(&now, &g->rate_limit_cfg);
	ev_token_bucket_update_(&g->rate_limit, &g->rate_limit_cfg, tick);

	if (g->pending_unsuspend_read ||
	    (g->read_suspended && (g->rate_limit.read_limit >= g->min_share))) {
		bev_group_unsuspend_reading_(g);
	}
	if (g->pending_unsuspend_write ||
	    (g->write_suspended && (g->rate_limit.write_limit >= g->min_share))){
		bev_group_unsuspend_writing_(g);
	}

	/* XXXX Rather than waiting to the next tick to unsuspend stuff
	 * with pending_unsuspend_write/read, we should do it on the
	 * next iteration of the mainloop.
	 */

	UNLOCK_GROUP(g);
}