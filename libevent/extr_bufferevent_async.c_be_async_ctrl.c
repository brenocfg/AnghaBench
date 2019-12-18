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
union bufferevent_ctrl_data {void* fd; } ;
struct event_iocp_port {int dummy; } ;
struct TYPE_2__ {int options; } ;
struct bufferevent_async {int ok; TYPE_1__ bev; } ;
struct bufferevent {int /*<<< orphan*/  input; int /*<<< orphan*/  output; int /*<<< orphan*/  ev_base; } ;
typedef  void* evutil_socket_t ;
typedef  enum bufferevent_ctrl_op { ____Placeholder_bufferevent_ctrl_op } bufferevent_ctrl_op ;

/* Variables and functions */
#define  BEV_CTRL_CANCEL_ALL 131 
#define  BEV_CTRL_GET_FD 130 
#define  BEV_CTRL_GET_UNDERLYING 129 
#define  BEV_CTRL_SET_FD 128 
 int BEV_OPT_CLOSE_ON_FREE ; 
 void* EVUTIL_INVALID_SOCKET ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  closesocket (void*) ; 
 void* evbuffer_overlapped_get_fd_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_overlapped_set_fd_ (int /*<<< orphan*/ ,void*) ; 
 struct event_iocp_port* event_base_get_iocp_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_iocp_port_associate_ (struct event_iocp_port*,void*,int) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ) ; 
 struct bufferevent_async* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_async_ctrl(struct bufferevent *bev, enum bufferevent_ctrl_op op,
    union bufferevent_ctrl_data *data)
{
	switch (op) {
	case BEV_CTRL_GET_FD:
		data->fd = evbuffer_overlapped_get_fd_(bev->input);
		return 0;
	case BEV_CTRL_SET_FD: {
		struct bufferevent_async *bev_a = upcast(bev);
		struct event_iocp_port *iocp;

		if (data->fd == evbuffer_overlapped_get_fd_(bev->input))
			return 0;
		if (!(iocp = event_base_get_iocp_(bev->ev_base)))
			return -1;
		if (event_iocp_port_associate_(iocp, data->fd, 1) < 0) {
			if (fatal_error(GetLastError()))
				return -1;
		}
		evbuffer_overlapped_set_fd_(bev->input, data->fd);
		evbuffer_overlapped_set_fd_(bev->output, data->fd);
		bev_a->ok = data->fd >= 0;
		return 0;
	}
	case BEV_CTRL_CANCEL_ALL: {
		struct bufferevent_async *bev_a = upcast(bev);
		evutil_socket_t fd = evbuffer_overlapped_get_fd_(bev->input);
		if (fd != (evutil_socket_t)EVUTIL_INVALID_SOCKET &&
		    (bev_a->bev.options & BEV_OPT_CLOSE_ON_FREE)) {
			closesocket(fd);
			evbuffer_overlapped_set_fd_(bev->input, EVUTIL_INVALID_SOCKET);
		}
		bev_a->ok = 0;
		return 0;
	}
	case BEV_CTRL_GET_UNDERLYING:
	default:
		return -1;
	}
}