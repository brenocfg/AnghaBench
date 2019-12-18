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
struct bufferevent_rate_limit_group {int read_suspended; int write_suspended; int /*<<< orphan*/  members; int /*<<< orphan*/  n_members; } ;
struct bufferevent_rate_limit {struct bufferevent_rate_limit_group* group; int /*<<< orphan*/  refill_bucket_event; } ;
struct bufferevent_private {struct bufferevent_rate_limit* rate_limiting; } ;
struct bufferevent {int /*<<< orphan*/  ev_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_in_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_SUSPEND_BW_GROUP ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EV_FINALIZE ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bufferevent_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  UNLOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  bev_refill_callback_ ; 
 int /*<<< orphan*/  bufferevent_remove_from_rate_limit_group (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_suspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_suspend_write_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_private*) ; 
 struct bufferevent_rate_limit* mm_calloc (int,int) ; 
 TYPE_1__* rate_limiting ; 

int
bufferevent_add_to_rate_limit_group(struct bufferevent *bev,
    struct bufferevent_rate_limit_group *g)
{
	int wsuspend, rsuspend;
	struct bufferevent_private *bevp = BEV_UPCAST(bev);
	BEV_LOCK(bev);

	if (!bevp->rate_limiting) {
		struct bufferevent_rate_limit *rlim;
		rlim = mm_calloc(1, sizeof(struct bufferevent_rate_limit));
		if (!rlim) {
			BEV_UNLOCK(bev);
			return -1;
		}
		event_assign(&rlim->refill_bucket_event, bev->ev_base,
		    -1, EV_FINALIZE, bev_refill_callback_, bevp);
		bevp->rate_limiting = rlim;
	}

	if (bevp->rate_limiting->group == g) {
		BEV_UNLOCK(bev);
		return 0;
	}
	if (bevp->rate_limiting->group)
		bufferevent_remove_from_rate_limit_group(bev);

	LOCK_GROUP(g);
	bevp->rate_limiting->group = g;
	++g->n_members;
	LIST_INSERT_HEAD(&g->members, bevp, rate_limiting->next_in_group);

	rsuspend = g->read_suspended;
	wsuspend = g->write_suspended;

	UNLOCK_GROUP(g);

	if (rsuspend)
		bufferevent_suspend_read_(bev, BEV_SUSPEND_BW_GROUP);
	if (wsuspend)
		bufferevent_suspend_write_(bev, BEV_SUSPEND_BW_GROUP);

	BEV_UNLOCK(bev);
	return 0;
}