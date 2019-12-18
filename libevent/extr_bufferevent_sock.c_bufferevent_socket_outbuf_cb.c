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
struct evbuffer_cb_info {scalar_t__ n_added; } ;
struct evbuffer {int dummy; } ;
struct bufferevent_private {int /*<<< orphan*/  write_suspended; } ;
struct bufferevent {int enabled; int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_write; } ;

/* Variables and functions */
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int EV_WRITE ; 
 int bufferevent_add_event_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_pending (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bufferevent_socket_outbuf_cb(struct evbuffer *buf,
    const struct evbuffer_cb_info *cbinfo,
    void *arg)
{
	struct bufferevent *bufev = arg;
	struct bufferevent_private *bufev_p = BEV_UPCAST(bufev);

	if (cbinfo->n_added &&
	    (bufev->enabled & EV_WRITE) &&
	    !event_pending(&bufev->ev_write, EV_WRITE, NULL) &&
	    !bufev_p->write_suspended) {
		/* Somebody added data to the buffer, and we would like to
		 * write, and we were not writing.  So, start writing. */
		if (bufferevent_add_event_(&bufev->ev_write, &bufev->timeout_write) == -1) {
		    /* Should we log this? */
		}
	}
}