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
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 struct evbuffer* bufferevent_get_output (struct bufferevent*) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 

__attribute__((used)) static void
done_writing_cb(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *b = bufferevent_get_output(bev);
	if (evbuffer_get_length(b))
		return;
	TT_BLATHER(("Done writing."));
	bufferevent_disable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
}