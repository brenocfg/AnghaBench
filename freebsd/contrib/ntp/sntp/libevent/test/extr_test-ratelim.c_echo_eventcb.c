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
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  n_echo_conns_open ; 

__attribute__((used)) static void
echo_eventcb(struct bufferevent *bev, short what, void *ctx)
{
	if (what & (BEV_EVENT_EOF|BEV_EVENT_ERROR)) {
		--n_echo_conns_open;
		bufferevent_free(bev);
	}
}