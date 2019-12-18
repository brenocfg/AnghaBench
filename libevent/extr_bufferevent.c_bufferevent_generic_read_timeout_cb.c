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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int BEV_EVENT_READING ; 
 int BEV_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_incref_and_lock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufferevent_generic_read_timeout_cb(evutil_socket_t fd, short event, void *ctx)
{
	struct bufferevent *bev = ctx;
	bufferevent_incref_and_lock_(bev);
	bufferevent_disable(bev, EV_READ);
	bufferevent_run_eventcb_(bev, BEV_EVENT_TIMEOUT|BEV_EVENT_READING, 0);
	bufferevent_decref_and_unlock_(bev);
}