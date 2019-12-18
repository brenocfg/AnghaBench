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
struct bufferevent_openssl {TYPE_1__ bev; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_TIMEOUT ; 
 short EV_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_incref_and_lock_ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_handshake (struct bufferevent_openssl*) ; 

__attribute__((used)) static void
be_openssl_handshakeeventcb(evutil_socket_t fd, short what, void *ptr)
{
	struct bufferevent_openssl *bev_ssl = ptr;

	bufferevent_incref_and_lock_(&bev_ssl->bev.bev);
	if (what & EV_TIMEOUT) {
		bufferevent_run_eventcb_(&bev_ssl->bev.bev, BEV_EVENT_TIMEOUT, 0);
	} else
		do_handshake(bev_ssl);/* XXX handle failure */
	bufferevent_decref_and_unlock_(&bev_ssl->bev.bev);
}