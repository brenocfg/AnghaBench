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
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int BEV_EVENT_EOF ; 
 int BEV_EVENT_READING ; 
 int /*<<< orphan*/  BEV_FINISHED ; 
 int /*<<< orphan*/  EVLOOP_ONCE ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 scalar_t__ bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_flush (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 scalar_t__ bufferevent_pair_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent**) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  event_base_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pair_flush_eventcb ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_bufferevent_pair_flush(void *arg)
{
	struct basic_test_data *data = arg;
	struct bufferevent *pair[2];
	struct bufferevent *bev1 = NULL;
	struct bufferevent *bev2 = NULL;
	int callback_what = 0;

	tt_assert(0 == bufferevent_pair_new(data->base, 0, pair));
	bev1 = pair[0];
	bev2 = pair[1];
	tt_assert(0 == bufferevent_enable(bev1, EV_WRITE));
	tt_assert(0 == bufferevent_enable(bev2, EV_READ));

	bufferevent_setcb(bev2, NULL, NULL, pair_flush_eventcb, &callback_what);

	bufferevent_flush(bev1, EV_WRITE, BEV_FINISHED);

	event_base_loop(data->base, EVLOOP_ONCE);

	tt_assert(callback_what == (BEV_EVENT_READING | BEV_EVENT_EOF));

end:
	if (bev1)
		bufferevent_free(bev1);
	if (bev2)
		bufferevent_free(bev2);
}