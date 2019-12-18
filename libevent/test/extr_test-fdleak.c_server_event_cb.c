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
 scalar_t__ MAX_REQUESTS ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_base (struct bufferevent*) ; 
 int /*<<< orphan*/  event_base_loopbreak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  my_perror (char*) ; 
 scalar_t__ num_requests ; 

__attribute__((used)) static void
server_event_cb(struct bufferevent *bev, short events, void *ctx)
{
	if (events & BEV_EVENT_ERROR) {
		my_perror("Error from bufferevent");
		exit(1);
	} else if (events & BEV_EVENT_EOF) {
		bufferevent_free(bev);
		if (num_requests == MAX_REQUESTS) {
			event_base_loopbreak(bufferevent_get_base(bev));
		}
	}
}