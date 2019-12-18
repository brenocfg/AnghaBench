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
struct wm_context {scalar_t__ get; scalar_t__ server; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 

__attribute__((used)) static void
wm_eventcb(struct bufferevent *bev, short what, void *arg)
{
	struct wm_context *ctx = arg;
	TT_BLATHER(("wm_eventcb-%s(%p): %i",
		ctx->server ? "server" : "client", bev, what));
	if (what & BEV_EVENT_CONNECTED) {
	} else {
		ctx->get = 0;
	}
}