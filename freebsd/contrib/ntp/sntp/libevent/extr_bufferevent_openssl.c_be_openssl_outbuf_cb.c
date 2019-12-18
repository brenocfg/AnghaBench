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
struct evbuffer_cb_info {scalar_t__ orig_size; scalar_t__ n_added; } ;
struct evbuffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_write; } ;
struct TYPE_4__ {TYPE_1__ bev; } ;
struct bufferevent_openssl {scalar_t__ state; TYPE_2__ bev; } ;

/* Variables and functions */
 scalar_t__ BUFFEREVENT_SSL_OPEN ; 
 int bufferevent_add_event_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  consider_writing (struct bufferevent_openssl*) ; 

__attribute__((used)) static void
be_openssl_outbuf_cb(struct evbuffer *buf,
    const struct evbuffer_cb_info *cbinfo, void *arg)
{
	struct bufferevent_openssl *bev_ssl = arg;
	int r = 0;
	/* XXX need to hold a reference here. */

	if (cbinfo->n_added && bev_ssl->state == BUFFEREVENT_SSL_OPEN) {
		if (cbinfo->orig_size == 0)
			r = bufferevent_add_event_(&bev_ssl->bev.bev.ev_write,
			    &bev_ssl->bev.bev.timeout_write);
		consider_writing(bev_ssl);
	}
	/* XXX Handle r < 0 */
        (void)r;
}