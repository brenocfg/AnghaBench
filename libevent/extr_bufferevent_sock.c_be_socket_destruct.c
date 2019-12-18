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
struct bufferevent_private {int options; int /*<<< orphan*/  dns_request; } ;
struct bufferevent {int /*<<< orphan*/  ev_read; } ;
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_IS_SOCKET (struct bufferevent*) ; 
 int BEV_OPT_CLOSE_ON_FREE ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVUTIL_CLOSESOCKET (scalar_t__) ; 
 scalar_t__ event_get_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_getaddrinfo_cancel_async_ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_socket_destruct(struct bufferevent *bufev)
{
	struct bufferevent_private *bufev_p = BEV_UPCAST(bufev);
	evutil_socket_t fd;
	EVUTIL_ASSERT(BEV_IS_SOCKET(bufev));

	fd = event_get_fd(&bufev->ev_read);

	if ((bufev_p->options & BEV_OPT_CLOSE_ON_FREE) && fd >= 0)
		EVUTIL_CLOSESOCKET(fd);

	evutil_getaddrinfo_cancel_async_(bufev_p->dns_request);
}