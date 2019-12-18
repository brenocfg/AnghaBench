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
struct bufferevent_filtered {int /*<<< orphan*/  inbuf_cb; scalar_t__ got_eof; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;
typedef  enum bufferevent_filter_result { ____Placeholder_bufferevent_filter_result } bufferevent_filter_result ;

/* Variables and functions */
 int BEV_FINISHED ; 
 int BEV_NORMAL ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVBUFFER_CB_ENABLED ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  EV_READ ; 
 int be_filter_process_input (struct bufferevent_filtered*,int,int*) ; 
 scalar_t__ be_readbuf_full (struct bufferevent_filtered*,int) ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  evbuffer_cb_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_filter_read_nolock_(struct bufferevent *underlying, void *me_)
{
	struct bufferevent_filtered *bevf = me_;
	enum bufferevent_filter_result res;
	enum bufferevent_flush_mode state;
	struct bufferevent *bufev = downcast(bevf);
	struct bufferevent_private *bufev_private = BEV_UPCAST(bufev);
	int processed_any = 0;

	// It's possible our refcount is 0 at this point if another thread free'd our filterevent
	EVUTIL_ASSERT(bufev_private->refcnt >= 0);

	// If our refcount is > 0
	if (bufev_private->refcnt > 0) {

		if (bevf->got_eof)
			state = BEV_FINISHED;
		else
			state = BEV_NORMAL;

		/* XXXX use return value */
		res = be_filter_process_input(bevf, state, &processed_any);
		(void)res;

		/* XXX This should be in process_input, not here.  There are
		 * other places that can call process-input, and they should
		 * force readcb calls as needed. */
		if (processed_any) {
			bufferevent_trigger_nolock_(bufev, EV_READ, 0);
			if (evbuffer_get_length(underlying->input) > 0 &&
				be_readbuf_full(bevf, state)) {
				/* data left in underlying buffer and filter input buffer
				 * hit its read high watermark.
				 * Schedule callback to avoid data gets stuck in underlying
				 * input buffer.
				 */
				evbuffer_cb_set_flags(bufev->input, bevf->inbuf_cb,
					EVBUFFER_CB_ENABLED);
			}
		}
	}
}