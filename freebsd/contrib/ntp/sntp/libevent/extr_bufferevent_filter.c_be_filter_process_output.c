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
struct bufferevent_filtered {int (* process_out ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  outbuf_cb; int /*<<< orphan*/  context; TYPE_2__* underlying; } ;
struct bufferevent {int enabled; int /*<<< orphan*/  output; } ;
typedef  int ev_ssize_t ;
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;
typedef  enum bufferevent_filter_result { ____Placeholder_bufferevent_filter_result } bufferevent_filter_result ;
struct TYPE_3__ {int high; } ;
struct TYPE_4__ {int /*<<< orphan*/  output; TYPE_1__ wm_write; } ;

/* Variables and functions */
 int BEV_NORMAL ; 
 int BEV_OK ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  EVBUFFER_CB_ENABLED ; 
 int EV_WRITE ; 
 scalar_t__ be_underlying_writebuf_full (struct bufferevent_filtered*,int) ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int,int /*<<< orphan*/ ) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  evbuffer_cb_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bufferevent_filter_result
be_filter_process_output(struct bufferevent_filtered *bevf,
			 enum bufferevent_flush_mode state,
			 int *processed_out)
{
	/* Requires references and lock: might call writecb */
	enum bufferevent_filter_result res = BEV_OK;
	struct bufferevent *bufev = downcast(bevf);
	int again = 0;

	if (state == BEV_NORMAL) {
		/* If we're in 'normal' mode, don't urge data on the
		 * filter unless we're writing data, and the underlying
		 * bufferevent is accepting data, and we have data to
		 * give the filter.  If we're in 'flush' or 'finish',
		 * call the filter no matter what. */
		if (!(bufev->enabled & EV_WRITE) ||
		    be_underlying_writebuf_full(bevf, state) ||
		    !evbuffer_get_length(bufev->output))
			return BEV_OK;
	}

	/* disable the callback that calls this function
	   when the user adds to the output buffer. */
	evbuffer_cb_set_flags(bufev->output, bevf->outbuf_cb, 0);

	do {
		int processed = 0;
		again = 0;

		do {
			ev_ssize_t limit = -1;
			if (state == BEV_NORMAL &&
			    bevf->underlying->wm_write.high)
				limit = bevf->underlying->wm_write.high -
				    evbuffer_get_length(bevf->underlying->output);

			res = bevf->process_out(downcast(bevf)->output,
			    bevf->underlying->output,
			    limit,
			    state,
			    bevf->context);

			if (res == BEV_OK)
				processed = *processed_out = 1;
		} while (/* Stop if the filter wasn't successful...*/
			res == BEV_OK &&
			/* Or if we aren't writing any more. */
			(bufev->enabled & EV_WRITE) &&
			/* Of if we have nothing more to write and we are
			 * not flushing. */
			evbuffer_get_length(bufev->output) &&
			/* Or if we have filled the underlying output buffer. */
			!be_underlying_writebuf_full(bevf,state));

		if (processed) {
			/* call the write callback.*/
			bufferevent_trigger_nolock_(bufev, EV_WRITE, 0);

			if (res == BEV_OK &&
			    (bufev->enabled & EV_WRITE) &&
			    evbuffer_get_length(bufev->output) &&
			    !be_underlying_writebuf_full(bevf, state)) {
				again = 1;
			}
		}
	} while (again);

	/* reenable the outbuf_cb */
	evbuffer_cb_set_flags(bufev->output,bevf->outbuf_cb,
	    EVBUFFER_CB_ENABLED);

	if (*processed_out)
		BEV_RESET_GENERIC_WRITE_TIMEOUT(bufev);

	return res;
}