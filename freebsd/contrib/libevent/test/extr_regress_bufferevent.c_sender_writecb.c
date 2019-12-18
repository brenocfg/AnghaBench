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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 scalar_t__ bufferevent_getfd (struct bufferevent*) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sender_writecb(struct bufferevent *bev, void *ctx)
{
	if (evbuffer_get_length(bufferevent_get_output(bev)) == 0) {
		bufferevent_disable(bev,EV_READ|EV_WRITE);
		TT_BLATHER(("Flushed %d: freeing it.", (int)bufferevent_getfd(bev)));
		bufferevent_free(bev);
	}
}