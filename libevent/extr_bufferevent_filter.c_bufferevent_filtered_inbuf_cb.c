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
struct evbuffer_cb_info {int dummy; } ;
struct evbuffer {int dummy; } ;
struct bufferevent_filtered {TYPE_1__* underlying; int /*<<< orphan*/  inbuf_cb; scalar_t__ got_eof; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int BEV_FINISHED ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int BEV_NORMAL ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  EVBUFFER_CB_ENABLED ; 
 int /*<<< orphan*/  be_filter_read_nolock_ (TYPE_1__*,struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  be_readbuf_full (struct bufferevent_filtered*,int) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  evbuffer_cb_clear_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufferevent_filtered_inbuf_cb(struct evbuffer *buf,
    const struct evbuffer_cb_info *cbinfo, void *arg)
{
	struct bufferevent_filtered *bevf = arg;
	enum bufferevent_flush_mode state;
	struct bufferevent *bev = downcast(bevf);

	BEV_LOCK(bev);

	if (bevf->got_eof)
		state = BEV_FINISHED;
	else
		state = BEV_NORMAL;


	if (!be_readbuf_full(bevf, state)) {
		/* opportunity to read data which was left in underlying
		 * input buffer because filter input buffer hit read
		 * high watermark.
		 */
		evbuffer_cb_clear_flags(bev->input, bevf->inbuf_cb,
			EVBUFFER_CB_ENABLED);
		if (evbuffer_get_length(bevf->underlying->input) > 0)
			be_filter_read_nolock_(bevf->underlying, bevf);
	}

	BEV_UNLOCK(bev);
}