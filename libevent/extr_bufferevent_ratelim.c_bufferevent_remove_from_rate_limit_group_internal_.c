#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bufferevent_rate_limit_group {int /*<<< orphan*/  n_members; } ;
struct bufferevent_private {TYPE_1__* rate_limiting; } ;
struct bufferevent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_in_group; } ;
struct TYPE_3__ {struct bufferevent_rate_limit_group* group; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_SUSPEND_BW_GROUP ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bufferevent_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  UNLOCK_GROUP (struct bufferevent_rate_limit_group*) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_write_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 TYPE_2__* rate_limiting ; 

int
bufferevent_remove_from_rate_limit_group_internal_(struct bufferevent *bev,
    int unsuspend)
{
	struct bufferevent_private *bevp = BEV_UPCAST(bev);
	BEV_LOCK(bev);
	if (bevp->rate_limiting && bevp->rate_limiting->group) {
		struct bufferevent_rate_limit_group *g =
		    bevp->rate_limiting->group;
		LOCK_GROUP(g);
		bevp->rate_limiting->group = NULL;
		--g->n_members;
		LIST_REMOVE(bevp, rate_limiting->next_in_group);
		UNLOCK_GROUP(g);
	}
	if (unsuspend) {
		bufferevent_unsuspend_read_(bev, BEV_SUSPEND_BW_GROUP);
		bufferevent_unsuspend_write_(bev, BEV_SUSPEND_BW_GROUP);
	}
	BEV_UNLOCK(bev);
	return 0;
}