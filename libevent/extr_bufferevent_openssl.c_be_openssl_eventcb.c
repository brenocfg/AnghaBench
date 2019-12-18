#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bev; } ;
struct bufferevent_openssl {TYPE_1__ bev; scalar_t__ allow_dirty_shutdown; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 short BEV_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_openssl_eventcb(struct bufferevent *bev_base, short what, void *ctx)
{
	struct bufferevent_openssl *bev_ssl = ctx;
	int event = 0;

	if (what & BEV_EVENT_EOF) {
		if (bev_ssl->allow_dirty_shutdown)
			event = BEV_EVENT_EOF;
		else
			event = BEV_EVENT_ERROR;
	} else if (what & BEV_EVENT_TIMEOUT) {
		/* We sure didn't set this.  Propagate it to the user. */
		event = what;
	} else if (what & BEV_EVENT_ERROR) {
		/* An error occurred on the connection.  Propagate it to the user. */
		event = what;
	} else if (what & BEV_EVENT_CONNECTED) {
		/* Ignore it.  We're saying SSL_connect() already, which will
		   eat it. */
	}
	if (event)
		bufferevent_run_eventcb_(&bev_ssl->bev.bev, event, 0);
}