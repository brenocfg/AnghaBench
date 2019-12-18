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
struct evutil_addrinfo {scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
struct bufferevent_private {int dns_error; int /*<<< orphan*/ * dns_request; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_ERROR ; 
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_SUSPEND_LOOKUP ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int EVUTIL_EAI_CANCEL ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bufferevent_socket_connect (struct bufferevent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bufferevent_socket_set_conn_address_ (struct bufferevent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_unsuspend_write_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (struct evutil_addrinfo*) ; 

__attribute__((used)) static void
bufferevent_connect_getaddrinfo_cb(int result, struct evutil_addrinfo *ai,
    void *arg)
{
	struct bufferevent *bev = arg;
	struct bufferevent_private *bev_p = BEV_UPCAST(bev);
	int r;
	BEV_LOCK(bev);

	bufferevent_unsuspend_write_(bev, BEV_SUSPEND_LOOKUP);
	bufferevent_unsuspend_read_(bev, BEV_SUSPEND_LOOKUP);

	bev_p->dns_request = NULL;

	if (result == EVUTIL_EAI_CANCEL) {
		bev_p->dns_error = result;
		bufferevent_decref_and_unlock_(bev);
		return;
	}
	if (result != 0) {
		bev_p->dns_error = result;
		bufferevent_run_eventcb_(bev, BEV_EVENT_ERROR, 0);
		bufferevent_decref_and_unlock_(bev);
		if (ai)
			evutil_freeaddrinfo(ai);
		return;
	}

	/* XXX use the other addrinfos? */
	bufferevent_socket_set_conn_address_(bev, ai->ai_addr, (int)ai->ai_addrlen);
	r = bufferevent_socket_connect(bev, ai->ai_addr, (int)ai->ai_addrlen);
	if (r < 0)
		bufferevent_run_eventcb_(bev, BEV_EVENT_ERROR, 0);
	bufferevent_decref_and_unlock_(bev);
	evutil_freeaddrinfo(ai);
}