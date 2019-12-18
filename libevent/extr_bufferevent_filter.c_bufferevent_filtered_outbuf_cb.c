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
struct bufferevent_filtered {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_NORMAL ; 
 int /*<<< orphan*/  be_filter_process_output (struct bufferevent_filtered*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_incref_and_lock_ (struct bufferevent*) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 

__attribute__((used)) static void
bufferevent_filtered_outbuf_cb(struct evbuffer *buf,
    const struct evbuffer_cb_info *cbinfo, void *arg)
{
	struct bufferevent_filtered *bevf = arg;
	struct bufferevent *bev = downcast(bevf);

	if (cbinfo->n_added) {
		int processed_any = 0;
		/* Somebody added more data to the output buffer. Try to
		 * process it, if we should. */
		bufferevent_incref_and_lock_(bev);
		be_filter_process_output(bevf, BEV_NORMAL, &processed_any);
		bufferevent_decref_and_unlock_(bev);
	}
}