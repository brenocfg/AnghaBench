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
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_get_input (struct bufferevent*) ; 
 scalar_t__ evbuffer_contains (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  event_base_loopexit (void*,int /*<<< orphan*/ *) ; 
 int test_ok ; 

__attribute__((used)) static void
http_failure_readcb(struct bufferevent *bev, void *arg)
{
	const char *what = "400 Bad Request";
	if (evbuffer_contains(bufferevent_get_input(bev), what)) {
		test_ok = 2;
		bufferevent_disable(bev, EV_READ);
		event_base_loopexit(arg, NULL);
	}
}