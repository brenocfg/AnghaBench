#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct win32_extension_fns {scalar_t__ (* ConnectEx ) (scalar_t__,struct sockaddr const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_family; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  overlapped; } ;
struct bufferevent_async {TYPE_2__ connect_overlapped; } ;
struct bufferevent {int /*<<< orphan*/  ev_base; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  scalar_t__ evutil_socket_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ ERROR_IO_PENDING ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ WSAEINVAL ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bufferevent_decref_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_incref_ (struct bufferevent*) ; 
 int /*<<< orphan*/  event_base_add_virtual_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_del_virtual_ (int /*<<< orphan*/ ) ; 
 struct win32_extension_fns* event_get_win32_extension_fns_ () ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (scalar_t__,struct sockaddr const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bufferevent_async* upcast (struct bufferevent*) ; 

int
bufferevent_async_connect_(struct bufferevent *bev, evutil_socket_t fd,
	const struct sockaddr *sa, int socklen)
{
	BOOL rc;
	struct bufferevent_async *bev_async = upcast(bev);
	struct sockaddr_storage ss;
	const struct win32_extension_fns *ext =
	    event_get_win32_extension_fns_();

	EVUTIL_ASSERT(ext && ext->ConnectEx && fd >= 0 && sa != NULL);

	/* ConnectEx() requires that the socket be bound to an address
	 * with bind() before using, otherwise it will fail. We attempt
	 * to issue a bind() here, taking into account that the error
	 * code is set to WSAEINVAL when the socket is already bound. */
	memset(&ss, 0, sizeof(ss));
	if (sa->sa_family == AF_INET) {
		struct sockaddr_in *sin = (struct sockaddr_in *)&ss;
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = INADDR_ANY;
	} else if (sa->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&ss;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_addr = in6addr_any;
	} else {
		/* Well, the user will have to bind() */
		return -1;
	}
	if (bind(fd, (struct sockaddr *)&ss, sizeof(ss)) < 0 &&
	    WSAGetLastError() != WSAEINVAL)
		return -1;

	event_base_add_virtual_(bev->ev_base);
	bufferevent_incref_(bev);
	rc = ext->ConnectEx(fd, sa, socklen, NULL, 0, NULL,
			    &bev_async->connect_overlapped.overlapped);
	if (rc || WSAGetLastError() == ERROR_IO_PENDING)
		return 0;

	event_base_del_virtual_(bev->ev_base);
	bufferevent_decref_(bev);

	return -1;
}