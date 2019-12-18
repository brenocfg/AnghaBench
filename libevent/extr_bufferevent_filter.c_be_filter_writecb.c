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
struct bufferevent_private {scalar_t__ refcnt; } ;
struct bufferevent_filtered {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_NORMAL ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  be_filter_process_output (struct bufferevent_filtered*,int /*<<< orphan*/ ,int*) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 

__attribute__((used)) static void
be_filter_writecb(struct bufferevent *underlying, void *me_)
{
	struct bufferevent_filtered *bevf = me_;
	struct bufferevent *bev = downcast(bevf);
	struct bufferevent_private *bufev_private = BEV_UPCAST(bev);
	int processed_any = 0;

	BEV_LOCK(bev);

	// It's possible our refcount is 0 at this point if another thread free'd our filterevent
	EVUTIL_ASSERT(bufev_private->refcnt >= 0);

	// If our refcount is > 0
	if (bufev_private->refcnt > 0) {
		be_filter_process_output(bevf, BEV_NORMAL, &processed_any);
	}

	BEV_UNLOCK(bev);
}