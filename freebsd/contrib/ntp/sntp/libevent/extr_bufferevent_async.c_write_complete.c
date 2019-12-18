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
struct event_overlapped {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  output; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_async {int write_in_progress; scalar_t__ ok; TYPE_1__ bev; } ;
typedef  int /*<<< orphan*/  ev_uintptr_t ;
typedef  int ev_ssize_t ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 short BEV_EVENT_WRITING ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  bev_async_consider_writing (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bev_async_set_wsa_error (struct bufferevent*,struct event_overlapped*) ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_decrement_write_buckets_ (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_commit_write_ (int /*<<< orphan*/ ,int) ; 
 struct bufferevent_async* upcast_write (struct event_overlapped*) ; 

__attribute__((used)) static void
write_complete(struct event_overlapped *eo, ev_uintptr_t key,
    ev_ssize_t nbytes, int ok)
{
	struct bufferevent_async *bev_a = upcast_write(eo);
	struct bufferevent *bev = &bev_a->bev.bev;
	short what = BEV_EVENT_WRITING;
	ev_ssize_t amount_unwritten;

	BEV_LOCK(bev);
	EVUTIL_ASSERT(bev_a->write_in_progress);

	amount_unwritten = bev_a->write_in_progress - nbytes;
	evbuffer_commit_write_(bev->output, nbytes);
	bev_a->write_in_progress = 0;

	if (amount_unwritten)
		bufferevent_decrement_write_buckets_(&bev_a->bev,
		                                     -amount_unwritten);


	if (!ok)
		bev_async_set_wsa_error(bev, eo);

	if (bev_a->ok) {
		if (ok && nbytes) {
			BEV_RESET_GENERIC_WRITE_TIMEOUT(bev);
			bufferevent_trigger_nolock_(bev, EV_WRITE, 0);
			bev_async_consider_writing(bev_a);
		} else if (!ok) {
			what |= BEV_EVENT_ERROR;
			bev_a->ok = 0;
			bufferevent_run_eventcb_(bev, what, 0);
		} else if (!nbytes) {
			what |= BEV_EVENT_EOF;
			bev_a->ok = 0;
			bufferevent_run_eventcb_(bev, what, 0);
		}
	}

	bufferevent_decref_and_unlock_(bev);
}