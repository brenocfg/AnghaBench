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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct event_base {int dummy; } ;
struct ev_token_bucket_cfg {int /*<<< orphan*/  tick_timeout; } ;
struct bufferevent_rate_limit_group {int /*<<< orphan*/  weakrand_seed; int /*<<< orphan*/  lock; int /*<<< orphan*/  master_refill_event; int /*<<< orphan*/  rate_limit; int /*<<< orphan*/  members; int /*<<< orphan*/  rate_limit_cfg; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;
typedef  scalar_t__ ev_intptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_ALLOC_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int EV_FINALIZE ; 
 int EV_PERSIST ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bev_group_refill_callback_ ; 
 int /*<<< orphan*/  bufferevent_rate_limit_group_set_min_share (struct bufferevent_rate_limit_group*,int) ; 
 int /*<<< orphan*/  ev_token_bucket_get_tick_ (struct timeval*,struct ev_token_bucket_cfg const*) ; 
 int /*<<< orphan*/  ev_token_bucket_init_ (int /*<<< orphan*/ *,struct ev_token_bucket_cfg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,struct event_base*,int,int,int /*<<< orphan*/ ,struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  event_base_gettimeofday_cached (struct event_base*,struct timeval*) ; 
 int /*<<< orphan*/  evutil_weakrand_seed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ev_token_bucket_cfg const*,int) ; 
 struct bufferevent_rate_limit_group* mm_calloc (int,int) ; 

struct bufferevent_rate_limit_group *
bufferevent_rate_limit_group_new(struct event_base *base,
    const struct ev_token_bucket_cfg *cfg)
{
	struct bufferevent_rate_limit_group *g;
	struct timeval now;
	ev_uint32_t tick;

	event_base_gettimeofday_cached(base, &now);
	tick = ev_token_bucket_get_tick_(&now, cfg);

	g = mm_calloc(1, sizeof(struct bufferevent_rate_limit_group));
	if (!g)
		return NULL;
	memcpy(&g->rate_limit_cfg, cfg, sizeof(g->rate_limit_cfg));
	LIST_INIT(&g->members);

	ev_token_bucket_init_(&g->rate_limit, cfg, tick, 0);

	event_assign(&g->master_refill_event, base, -1, EV_PERSIST|EV_FINALIZE,
	    bev_group_refill_callback_, g);
	/*XXXX handle event_add failure */
	event_add(&g->master_refill_event, &cfg->tick_timeout);

	EVTHREAD_ALLOC_LOCK(g->lock, EVTHREAD_LOCKTYPE_RECURSIVE);

	bufferevent_rate_limit_group_set_min_share(g, 64);

	evutil_weakrand_seed_(&g->weakrand_seed,
	    (ev_uint32_t) ((now.tv_sec + now.tv_usec) + (ev_intptr_t)g));

	return g;
}