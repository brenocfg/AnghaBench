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
struct client_state {int queued; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct evbuffer* bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int evbuffer_get_length (struct evbuffer*) ; 
 int evutil_weakrand_ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  weakrand_state ; 

__attribute__((used)) static void
loud_writecb(struct bufferevent *bev, void *ctx)
{
	struct client_state *cs = ctx;
	struct evbuffer *output = bufferevent_get_output(bev);
	char buf[1024];
	int r = evutil_weakrand_(&weakrand_state);
	memset(buf, r, sizeof(buf));
	while (evbuffer_get_length(output) < 8192) {
		evbuffer_add(output, buf, sizeof(buf));
		cs->queued += sizeof(buf);
	}
}