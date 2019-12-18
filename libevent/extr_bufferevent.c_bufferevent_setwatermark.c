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
struct bufferevent_private {int /*<<< orphan*/ * read_watermarks_cb; } ;
struct TYPE_4__ {size_t low; size_t high; } ;
struct TYPE_3__ {size_t low; size_t high; } ;
struct bufferevent {int /*<<< orphan*/  input; TYPE_2__ wm_read; TYPE_1__ wm_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int EVBUFFER_CB_ENABLED ; 
 int EVBUFFER_CB_NODEFER ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_inbuf_wm_cb ; 
 int /*<<< orphan*/  bufferevent_wm_suspend_read (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_wm_unsuspend_read (struct bufferevent*) ; 
 int /*<<< orphan*/ * evbuffer_add_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_cb_clear_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evbuffer_cb_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 size_t evbuffer_get_length (int /*<<< orphan*/ ) ; 

void
bufferevent_setwatermark(struct bufferevent *bufev, short events,
    size_t lowmark, size_t highmark)
{
	struct bufferevent_private *bufev_private = BEV_UPCAST(bufev);

	BEV_LOCK(bufev);
	if (events & EV_WRITE) {
		bufev->wm_write.low = lowmark;
		bufev->wm_write.high = highmark;
	}

	if (events & EV_READ) {
		bufev->wm_read.low = lowmark;
		bufev->wm_read.high = highmark;

		if (highmark) {
			/* There is now a new high-water mark for read.
			   enable the callback if needed, and see if we should
			   suspend/bufferevent_wm_unsuspend. */

			if (bufev_private->read_watermarks_cb == NULL) {
				bufev_private->read_watermarks_cb =
				    evbuffer_add_cb(bufev->input,
						    bufferevent_inbuf_wm_cb,
						    bufev);
			}
			evbuffer_cb_set_flags(bufev->input,
				      bufev_private->read_watermarks_cb,
				      EVBUFFER_CB_ENABLED|EVBUFFER_CB_NODEFER);

			if (evbuffer_get_length(bufev->input) >= highmark)
				bufferevent_wm_suspend_read(bufev);
			else if (evbuffer_get_length(bufev->input) < highmark)
				bufferevent_wm_unsuspend_read(bufev);
		} else {
			/* There is now no high-water mark for read. */
			if (bufev_private->read_watermarks_cb)
				evbuffer_cb_clear_flags(bufev->input,
				    bufev_private->read_watermarks_cb,
				    EVBUFFER_CB_ENABLED);
			bufferevent_wm_unsuspend_read(bufev);
		}
	}
	BEV_UNLOCK(bufev);
}