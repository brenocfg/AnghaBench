#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t high; } ;
struct bufferevent {int enabled; int /*<<< orphan*/  input; TYPE_1__ wm_read; } ;
struct TYPE_5__ {scalar_t__ read_suspended; scalar_t__ connecting; struct bufferevent bev; } ;
struct bufferevent_async {size_t read_in_progress; TYPE_2__ bev; scalar_t__ ok; int /*<<< orphan*/  read_overlapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_ERROR ; 
 int EV_READ ; 
 int /*<<< orphan*/  bev_async_add_read (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bev_async_del_read (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bufferevent_decref_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_decrement_read_buckets_ (TYPE_2__*,size_t) ; 
 scalar_t__ bufferevent_get_read_max_ (TYPE_2__*) ; 
 int /*<<< orphan*/  bufferevent_incref_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t evbuffer_get_length (int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_launch_read_ (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bev_async_consider_reading(struct bufferevent_async *beva)
{
	size_t cur_size;
	size_t read_high;
	size_t at_most;
	int limit;
	struct bufferevent *bev = &beva->bev.bev;

	/* Don't read if there is a read in progress, or we do not
	 * want to read. */
	if (beva->read_in_progress || beva->bev.connecting)
		return;
	if (!beva->ok || !(bev->enabled&EV_READ)) {
		bev_async_del_read(beva);
		return;
	}

	/* Don't read if we're full */
	cur_size = evbuffer_get_length(bev->input);
	read_high = bev->wm_read.high;
	if (read_high) {
		if (cur_size >= read_high) {
			bev_async_del_read(beva);
			return;
		}
		at_most = read_high - cur_size;
	} else {
		at_most = 16384; /* FIXME totally magic. */
	}

	/* XXXX This over-commits. */
	/* XXXX see also not above on cast on bufferevent_get_write_max_() */
	limit = (int)bufferevent_get_read_max_(&beva->bev);
	if (at_most >= (size_t)limit && limit >= 0)
		at_most = limit;

	if (beva->bev.read_suspended) {
		bev_async_del_read(beva);
		return;
	}

	bufferevent_incref_(bev);
	if (evbuffer_launch_read_(bev->input, at_most, &beva->read_overlapped)) {
		beva->ok = 0;
		bufferevent_run_eventcb_(bev, BEV_EVENT_ERROR, 0);
		bufferevent_decref_(bev);
	} else {
		beva->read_in_progress = at_most;
		bufferevent_decrement_read_buckets_(&beva->bev, at_most);
		bev_async_add_read(beva);
	}

	return;
}