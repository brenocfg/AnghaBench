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
struct bufferevent_filtered {int (* process_in ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; TYPE_2__* underlying; } ;
struct TYPE_3__ {int high; } ;
struct bufferevent {int enabled; int /*<<< orphan*/  input; TYPE_1__ wm_read; } ;
typedef  int ev_ssize_t ;
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;
typedef  enum bufferevent_filter_result { ____Placeholder_bufferevent_filter_result } bufferevent_filter_result ;
struct TYPE_4__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int BEV_NORMAL ; 
 int BEV_OK ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int EV_READ ; 
 scalar_t__ be_readbuf_full (struct bufferevent_filtered*,int) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 
 int evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bufferevent_filter_result
be_filter_process_input(struct bufferevent_filtered *bevf,
			enum bufferevent_flush_mode state,
			int *processed_out)
{
	enum bufferevent_filter_result res;
	struct bufferevent *bev = downcast(bevf);

	if (state == BEV_NORMAL) {
		/* If we're in 'normal' mode, don't urge data on the filter
		 * unless we're reading data and under our high-water mark.*/
		if (!(bev->enabled & EV_READ) ||
		    be_readbuf_full(bevf, state))
			return BEV_OK;
	}

	do {
		ev_ssize_t limit = -1;
		if (state == BEV_NORMAL && bev->wm_read.high)
			limit = bev->wm_read.high -
			    evbuffer_get_length(bev->input);

		res = bevf->process_in(bevf->underlying->input,
		    bev->input, limit, state, bevf->context);

		if (res == BEV_OK)
			*processed_out = 1;
	} while (res == BEV_OK &&
		 (bev->enabled & EV_READ) &&
		 evbuffer_get_length(bevf->underlying->input) &&
		 !be_readbuf_full(bevf, state));

	if (*processed_out)
		BEV_RESET_GENERIC_READ_TIMEOUT(bev);

	return res;
}