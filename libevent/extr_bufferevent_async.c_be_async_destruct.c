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
struct bufferevent_private {int options; } ;
struct bufferevent_async {int /*<<< orphan*/  read_in_progress; int /*<<< orphan*/  write_in_progress; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ EVUTIL_INVALID_SOCKET ; 
 int /*<<< orphan*/  bev_async_del_read (struct bufferevent_async*) ; 
 int /*<<< orphan*/  bev_async_del_write (struct bufferevent_async*) ; 
 scalar_t__ evbuffer_overlapped_get_fd_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_overlapped_set_fd_ (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 struct bufferevent_async* upcast (struct bufferevent*) ; 

__attribute__((used)) static void
be_async_destruct(struct bufferevent *bev)
{
	struct bufferevent_async *bev_async = upcast(bev);
	struct bufferevent_private *bev_p = BEV_UPCAST(bev);
	evutil_socket_t fd;

	EVUTIL_ASSERT(!upcast(bev)->write_in_progress &&
			!upcast(bev)->read_in_progress);

	bev_async_del_read(bev_async);
	bev_async_del_write(bev_async);

	fd = evbuffer_overlapped_get_fd_(bev->input);
	if (fd != (evutil_socket_t)EVUTIL_INVALID_SOCKET &&
		(bev_p->options & BEV_OPT_CLOSE_ON_FREE)) {
		evutil_closesocket(fd);
		evbuffer_overlapped_set_fd_(bev->input, EVUTIL_INVALID_SOCKET);
	}
}