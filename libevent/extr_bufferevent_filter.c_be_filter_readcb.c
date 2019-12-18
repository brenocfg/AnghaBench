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
struct bufferevent_filtered {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  be_filter_read_nolock_ (struct bufferevent*,void*) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 

__attribute__((used)) static void
be_filter_readcb(struct bufferevent *underlying, void *me_)
{
	struct bufferevent_filtered *bevf = me_;
	struct bufferevent *bev = downcast(bevf);

	BEV_LOCK(bev);

	be_filter_read_nolock_(underlying, me_);

	BEV_UNLOCK(bev);
}