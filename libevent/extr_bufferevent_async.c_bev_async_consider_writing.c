#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bufferevent {int enabled; int /*<<< orphan*/  output; } ;
struct TYPE_3__ {scalar_t__ write_suspended; scalar_t__ connecting; struct bufferevent bev; } ;
struct bufferevent_async {size_t write_in_progress; TYPE_1__ bev; scalar_t__ ok; int /*<<< orphan*/  write_overlapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_ERROR ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  be_async_run_eventcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bev_async_add_write (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bev_async_del_write (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bufferevent_decref_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_decrement_write_buckets_ (TYPE_1__*,size_t) ; 
 scalar_t__ bufferevent_get_write_max_ (TYPE_1__*) ; 
 int /*<<< orphan*/  bufferevent_incref_ (struct bufferevent*) ; 
 size_t evbuffer_get_length (int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_launch_write_ (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bev_async_consider_writing(struct bufferevent_async *beva)
{
	size_t at_most;
	int limit;
	struct bufferevent *bev = &beva->bev.bev;

	/* Don't write if there's a write in progress, or we do not
	 * want to write, or when there's nothing left to write. */
	if (beva->write_in_progress || beva->bev.connecting)
		return;
	if (!beva->ok || !(bev->enabled&EV_WRITE) ||
	    !evbuffer_get_length(bev->output)) {
		bev_async_del_write(beva);
		return;
	}

	at_most = evbuffer_get_length(bev->output);

	/* This is safe so long as bufferevent_get_write_max never returns
	 * more than INT_MAX.  That's true for now. XXXX */
	limit = (int)bufferevent_get_write_max_(&beva->bev);
	if (at_most >= (size_t)limit && limit >= 0)
		at_most = limit;

	if (beva->bev.write_suspended) {
		bev_async_del_write(beva);
		return;
	}

	/*  XXXX doesn't respect low-water mark very well. */
	bufferevent_incref_(bev);
	if (evbuffer_launch_write_(bev->output, at_most,
	    &beva->write_overlapped)) {
		bufferevent_decref_(bev);
		beva->ok = 0;
		be_async_run_eventcb(bev, BEV_EVENT_ERROR, 0);
	} else {
		beva->write_in_progress = at_most;
		bufferevent_decrement_write_buckets_(&beva->bev, at_most);
		bev_async_add_write(beva);
	}
}