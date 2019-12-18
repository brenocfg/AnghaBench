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
struct bufferevent {int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  ev_read; int /*<<< orphan*/  ev_base; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_openssl {int fd_is_set; TYPE_1__ bev; scalar_t__ underlying; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int EV_FINALIZE ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  be_openssl_eventcb ; 
 int /*<<< orphan*/  be_openssl_handshakecb ; 
 int /*<<< orphan*/  be_openssl_handshakeeventcb ; 
 int bufferevent_add_event_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_setcb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_openssl*) ; 
 int do_handshake (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_get_fd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_handshake_callbacks(struct bufferevent_openssl *bev_ssl, evutil_socket_t fd)
{
	if (bev_ssl->underlying) {
		bufferevent_setcb(bev_ssl->underlying,
		    be_openssl_handshakecb, be_openssl_handshakecb,
		    be_openssl_eventcb,
		    bev_ssl);
		return do_handshake(bev_ssl);
	} else {
		struct bufferevent *bev = &bev_ssl->bev.bev;
		int r1=0, r2=0;
		if (fd < 0 && bev_ssl->fd_is_set)
			fd = event_get_fd(&bev->ev_read);
		if (bev_ssl->fd_is_set) {
			event_del(&bev->ev_read);
			event_del(&bev->ev_write);
		}
		event_assign(&bev->ev_read, bev->ev_base, fd,
		    EV_READ|EV_PERSIST|EV_FINALIZE,
		    be_openssl_handshakeeventcb, bev_ssl);
		event_assign(&bev->ev_write, bev->ev_base, fd,
		    EV_WRITE|EV_PERSIST|EV_FINALIZE,
		    be_openssl_handshakeeventcb, bev_ssl);
		if (fd >= 0) {
			r1 = bufferevent_add_event_(&bev->ev_read, &bev->timeout_read);
			r2 = bufferevent_add_event_(&bev->ev_write, &bev->timeout_write);
			bev_ssl->fd_is_set = 1;
		}
		return (r1<0 || r2<0) ? -1 : 0;
	}
}