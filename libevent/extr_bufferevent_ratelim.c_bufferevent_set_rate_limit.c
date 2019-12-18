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
struct ev_token_bucket_cfg {int /*<<< orphan*/  tick_timeout; } ;
struct TYPE_2__ {scalar_t__ read_limit; scalar_t__ write_limit; } ;
struct bufferevent_rate_limit {int /*<<< orphan*/  refill_bucket_event; TYPE_1__ limit; struct ev_token_bucket_cfg* cfg; } ;
struct bufferevent_private {struct bufferevent_rate_limit* rate_limiting; } ;
struct bufferevent {int /*<<< orphan*/  ev_base; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_SUSPEND_BW ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  EV_FINALIZE ; 
 int /*<<< orphan*/  bev_refill_callback_ ; 
 int /*<<< orphan*/  bufferevent_suspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_suspend_write_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_write_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_token_bucket_get_tick_ (struct timeval*,struct ev_token_bucket_cfg*) ; 
 int /*<<< orphan*/  ev_token_bucket_init_ (TYPE_1__*,struct ev_token_bucket_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_private*) ; 
 int /*<<< orphan*/  event_base_gettimeofday_cached (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 struct bufferevent_rate_limit* mm_calloc (int,int) ; 

int
bufferevent_set_rate_limit(struct bufferevent *bev,
    struct ev_token_bucket_cfg *cfg)
{
	struct bufferevent_private *bevp = BEV_UPCAST(bev);
	int r = -1;
	struct bufferevent_rate_limit *rlim;
	struct timeval now;
	ev_uint32_t tick;
	int reinit = 0, suspended = 0;
	/* XXX reference-count cfg */

	BEV_LOCK(bev);

	if (cfg == NULL) {
		if (bevp->rate_limiting) {
			rlim = bevp->rate_limiting;
			rlim->cfg = NULL;
			bufferevent_unsuspend_read_(bev, BEV_SUSPEND_BW);
			bufferevent_unsuspend_write_(bev, BEV_SUSPEND_BW);
			if (event_initialized(&rlim->refill_bucket_event))
				event_del(&rlim->refill_bucket_event);
		}
		r = 0;
		goto done;
	}

	event_base_gettimeofday_cached(bev->ev_base, &now);
	tick = ev_token_bucket_get_tick_(&now, cfg);

	if (bevp->rate_limiting && bevp->rate_limiting->cfg == cfg) {
		/* no-op */
		r = 0;
		goto done;
	}
	if (bevp->rate_limiting == NULL) {
		rlim = mm_calloc(1, sizeof(struct bufferevent_rate_limit));
		if (!rlim)
			goto done;
		bevp->rate_limiting = rlim;
	} else {
		rlim = bevp->rate_limiting;
	}
	reinit = rlim->cfg != NULL;

	rlim->cfg = cfg;
	ev_token_bucket_init_(&rlim->limit, cfg, tick, reinit);

	if (reinit) {
		EVUTIL_ASSERT(event_initialized(&rlim->refill_bucket_event));
		event_del(&rlim->refill_bucket_event);
	}
	event_assign(&rlim->refill_bucket_event, bev->ev_base,
	    -1, EV_FINALIZE, bev_refill_callback_, bevp);

	if (rlim->limit.read_limit > 0) {
		bufferevent_unsuspend_read_(bev, BEV_SUSPEND_BW);
	} else {
		bufferevent_suspend_read_(bev, BEV_SUSPEND_BW);
		suspended=1;
	}
	if (rlim->limit.write_limit > 0) {
		bufferevent_unsuspend_write_(bev, BEV_SUSPEND_BW);
	} else {
		bufferevent_suspend_write_(bev, BEV_SUSPEND_BW);
		suspended = 1;
	}

	if (suspended)
		event_add(&rlim->refill_bucket_event, &cfg->tick_timeout);

	r = 0;

done:
	BEV_UNLOCK(bev);
	return r;
}