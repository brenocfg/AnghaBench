#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  ev_read; } ;
struct TYPE_4__ {TYPE_2__ bev; } ;
struct bufferevent_openssl {int state; int /*<<< orphan*/  ssl; TYPE_1__ bev; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_CONNECTED ; 
 int /*<<< orphan*/  BEV_EVENT_READING ; 
#define  BUFFEREVENT_SSL_ACCEPTING 132 
#define  BUFFEREVENT_SSL_CONNECTING 131 
#define  BUFFEREVENT_SSL_OPEN 130 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
#define  SSL_ERROR_WANT_READ 129 
#define  SSL_ERROR_WANT_WRITE 128 
 int SSL_do_handshake (int /*<<< orphan*/ ) ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bufferevent_enable (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_closed (struct bufferevent_openssl*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  decrement_buckets (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  event_get_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_err (int) ; 
 int /*<<< orphan*/  set_open_callbacks (struct bufferevent_openssl*,int /*<<< orphan*/ ) ; 
 int start_reading (struct bufferevent_openssl*) ; 
 int start_writing (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  stop_reading (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  stop_writing (struct bufferevent_openssl*) ; 

__attribute__((used)) static int
do_handshake(struct bufferevent_openssl *bev_ssl)
{
	int r;

	switch (bev_ssl->state) {
	default:
	case BUFFEREVENT_SSL_OPEN:
		EVUTIL_ASSERT(0);
		return -1;
	case BUFFEREVENT_SSL_CONNECTING:
	case BUFFEREVENT_SSL_ACCEPTING:
		ERR_clear_error();
		r = SSL_do_handshake(bev_ssl->ssl);
		break;
	}
	decrement_buckets(bev_ssl);

	if (r==1) {
		evutil_socket_t fd = event_get_fd(&bev_ssl->bev.bev.ev_read);
		/* We're done! */
		bev_ssl->state = BUFFEREVENT_SSL_OPEN;
		set_open_callbacks(bev_ssl, fd); /* XXXX handle failure */
		/* Call do_read and do_write as needed */
		bufferevent_enable(&bev_ssl->bev.bev, bev_ssl->bev.bev.enabled);
		bufferevent_run_eventcb_(&bev_ssl->bev.bev,
		    BEV_EVENT_CONNECTED, 0);
		return 1;
	} else {
		int err = SSL_get_error(bev_ssl->ssl, r);
		print_err(err);
		switch (err) {
		case SSL_ERROR_WANT_WRITE:
			stop_reading(bev_ssl);
			return start_writing(bev_ssl);
		case SSL_ERROR_WANT_READ:
			stop_writing(bev_ssl);
			return start_reading(bev_ssl);
		default:
			conn_closed(bev_ssl, BEV_EVENT_READING, err, r);
			return -1;
		}
	}
}