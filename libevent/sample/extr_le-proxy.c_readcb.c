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
struct evbuffer {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int MAX_OUTPUT ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 struct evbuffer* bufferevent_get_input (struct bufferevent*) ; 
 struct evbuffer* bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,void (*) (struct bufferevent*,void*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setwatermark (struct bufferevent*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  drained_writecb ; 
 int /*<<< orphan*/  evbuffer_add_buffer (struct evbuffer*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 int evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  eventcb ; 

__attribute__((used)) static void
readcb(struct bufferevent *bev, void *ctx)
{
	struct bufferevent *partner = ctx;
	struct evbuffer *src, *dst;
	size_t len;
	src = bufferevent_get_input(bev);
	len = evbuffer_get_length(src);
	if (!partner) {
		evbuffer_drain(src, len);
		return;
	}
	dst = bufferevent_get_output(partner);
	evbuffer_add_buffer(dst, src);

	if (evbuffer_get_length(dst) >= MAX_OUTPUT) {
		/* We're giving the other side data faster than it can
		 * pass it on.  Stop reading here until we have drained the
		 * other side to MAX_OUTPUT/2 bytes. */
		bufferevent_setcb(partner, readcb, drained_writecb,
		    eventcb, bev);
		bufferevent_setwatermark(partner, EV_WRITE, MAX_OUTPUT/2,
		    MAX_OUTPUT);
		bufferevent_disable(bev, EV_READ);
	}
}