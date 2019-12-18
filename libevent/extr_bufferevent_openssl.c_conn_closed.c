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
struct bufferevent_openssl {TYPE_1__ bev; scalar_t__ allow_dirty_shutdown; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int BEV_EVENT_EOF ; 
 int BEV_EVENT_ERROR ; 
 unsigned long ERR_get_error () ; 
 int /*<<< orphan*/  ERR_peek_error () ; 
#define  SSL_ERROR_NONE 136 
#define  SSL_ERROR_SSL 135 
#define  SSL_ERROR_SYSCALL 134 
#define  SSL_ERROR_WANT_ACCEPT 133 
#define  SSL_ERROR_WANT_CONNECT 132 
#define  SSL_ERROR_WANT_READ 131 
#define  SSL_ERROR_WANT_WRITE 130 
#define  SSL_ERROR_WANT_X509_LOOKUP 129 
#define  SSL_ERROR_ZERO_RETURN 128 
 int SSL_RECEIVED_SHUTDOWN ; 
 int SSL_get_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_warnx (char*,int) ; 
 int /*<<< orphan*/  put_error (struct bufferevent_openssl*,unsigned long) ; 
 int /*<<< orphan*/  stop_reading (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  stop_writing (struct bufferevent_openssl*) ; 

__attribute__((used)) static void
conn_closed(struct bufferevent_openssl *bev_ssl, int when, int errcode, int ret)
{
	int event = BEV_EVENT_ERROR;
	int dirty_shutdown = 0;
	unsigned long err;

	switch (errcode) {
	case SSL_ERROR_ZERO_RETURN:
		/* Possibly a clean shutdown. */
		if (SSL_get_shutdown(bev_ssl->ssl) & SSL_RECEIVED_SHUTDOWN)
			event = BEV_EVENT_EOF;
		else
			dirty_shutdown = 1;
		break;
	case SSL_ERROR_SYSCALL:
		/* IO error; possibly a dirty shutdown. */
		if ((ret == 0 || ret == -1) && ERR_peek_error() == 0)
			dirty_shutdown = 1;
		put_error(bev_ssl, errcode);
		break;
	case SSL_ERROR_SSL:
		/* Protocol error. */
		put_error(bev_ssl, errcode);
		break;
	case SSL_ERROR_WANT_X509_LOOKUP:
		/* XXXX handle this. */
		put_error(bev_ssl, errcode);
		break;
	case SSL_ERROR_NONE:
	case SSL_ERROR_WANT_READ:
	case SSL_ERROR_WANT_WRITE:
	case SSL_ERROR_WANT_CONNECT:
	case SSL_ERROR_WANT_ACCEPT:
	default:
		/* should be impossible; treat as normal error. */
		event_warnx("BUG: Unexpected OpenSSL error code %d", errcode);
		break;
	}

	while ((err = ERR_get_error())) {
		put_error(bev_ssl, err);
	}

	if (dirty_shutdown && bev_ssl->allow_dirty_shutdown)
		event = BEV_EVENT_EOF;

	stop_reading(bev_ssl);
	stop_writing(bev_ssl);

	/* when is BEV_EVENT_{READING|WRITING} */
	event = when | event;
	bufferevent_run_eventcb_(&bev_ssl->bev.bev, event, 0);
}