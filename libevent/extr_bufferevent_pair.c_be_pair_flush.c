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
struct bufferevent_pair {int /*<<< orphan*/  partner; } ;
struct bufferevent {int dummy; } ;
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_READING ; 
 short BEV_EVENT_WRITING ; 
 int BEV_FINISHED ; 
 int BEV_NORMAL ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  be_pair_transfer (struct bufferevent*,struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decref_and_unlock (struct bufferevent*) ; 
 struct bufferevent* downcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incref_and_lock (struct bufferevent*) ; 
 struct bufferevent_pair* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_pair_flush(struct bufferevent *bev, short iotype,
    enum bufferevent_flush_mode mode)
{
	struct bufferevent_pair *bev_p = upcast(bev);
	struct bufferevent *partner;

	if (!bev_p->partner)
		return -1;

	if (mode == BEV_NORMAL)
		return 0;

	incref_and_lock(bev);

	partner = downcast(bev_p->partner);

	if ((iotype & EV_READ) != 0)
		be_pair_transfer(partner, bev, 1);

	if ((iotype & EV_WRITE) != 0)
		be_pair_transfer(bev, partner, 1);

	if (mode == BEV_FINISHED) {
		short what = BEV_EVENT_EOF;
		if (iotype & EV_READ)
			what |= BEV_EVENT_WRITING;
		if (iotype & EV_WRITE)
			what |= BEV_EVENT_READING;
		bufferevent_run_eventcb_(partner, what, 0);
	}
	decref_and_unlock(bev);
	return 0;
}