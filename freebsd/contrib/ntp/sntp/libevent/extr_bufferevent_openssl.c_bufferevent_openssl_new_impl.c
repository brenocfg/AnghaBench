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
struct event_base {int dummy; } ;
struct bufferevent {int enabled; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; int /*<<< orphan*/  output; } ;
struct bufferevent_private {struct bufferevent bev; } ;
struct bufferevent_openssl {int state; int last_write; struct bufferevent_private bev; scalar_t__ fd_is_set; int /*<<< orphan*/ * ssl; int /*<<< orphan*/  outbuf_cb; struct bufferevent* underlying; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  enum bufferevent_ssl_state { ____Placeholder_bufferevent_ssl_state } bufferevent_ssl_state ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int BEV_OPT_THREADSAFE ; 
 int /*<<< orphan*/  BEV_SUSPEND_FILT_READ ; 
#define  BUFFEREVENT_SSL_ACCEPTING 130 
#define  BUFFEREVENT_SSL_CONNECTING 129 
#define  BUFFEREVENT_SSL_OPEN 128 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_openssl_outbuf_cb ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_enable_locking_ (struct bufferevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_incref_ (struct bufferevent*) ; 
 scalar_t__ bufferevent_init_common_ (struct bufferevent_private*,struct event_base*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufferevent_init_generic_timeout_cbs_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_ops_openssl ; 
 int /*<<< orphan*/  bufferevent_setwatermark (struct bufferevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_suspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_openssl*) ; 
 scalar_t__ event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_bio_counts (struct bufferevent_openssl*) ; 
 struct bufferevent_openssl* mm_calloc (int,int) ; 
 int /*<<< orphan*/  set_handshake_callbacks (struct bufferevent_openssl*,scalar_t__) ; 
 int /*<<< orphan*/  set_open_callbacks (struct bufferevent_openssl*,scalar_t__) ; 

__attribute__((used)) static struct bufferevent *
bufferevent_openssl_new_impl(struct event_base *base,
    struct bufferevent *underlying,
    evutil_socket_t fd,
    SSL *ssl,
    enum bufferevent_ssl_state state,
    int options)
{
	struct bufferevent_openssl *bev_ssl = NULL;
	struct bufferevent_private *bev_p = NULL;
	int tmp_options = options & ~BEV_OPT_THREADSAFE;

	if (underlying != NULL && fd >= 0)
		return NULL; /* Only one can be set. */

	if (!(bev_ssl = mm_calloc(1, sizeof(struct bufferevent_openssl))))
		goto err;

	bev_p = &bev_ssl->bev;

	if (bufferevent_init_common_(bev_p, base,
		&bufferevent_ops_openssl, tmp_options) < 0)
		goto err;

	/* Don't explode if we decide to realloc a chunk we're writing from in
	 * the output buffer. */
	SSL_set_mode(ssl, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);

	bev_ssl->underlying = underlying;
	bev_ssl->ssl = ssl;

	bev_ssl->outbuf_cb = evbuffer_add_cb(bev_p->bev.output,
	    be_openssl_outbuf_cb, bev_ssl);

	if (options & BEV_OPT_THREADSAFE)
		bufferevent_enable_locking_(&bev_ssl->bev.bev, NULL);

	if (underlying) {
		bufferevent_init_generic_timeout_cbs_(&bev_ssl->bev.bev);
		bufferevent_incref_(underlying);
	}

	bev_ssl->state = state;
	bev_ssl->last_write = -1;

	init_bio_counts(bev_ssl);

	switch (state) {
	case BUFFEREVENT_SSL_ACCEPTING:
		SSL_set_accept_state(bev_ssl->ssl);
		if (set_handshake_callbacks(bev_ssl, fd) < 0)
			goto err;
		break;
	case BUFFEREVENT_SSL_CONNECTING:
		SSL_set_connect_state(bev_ssl->ssl);
		if (set_handshake_callbacks(bev_ssl, fd) < 0)
			goto err;
		break;
	case BUFFEREVENT_SSL_OPEN:
		if (set_open_callbacks(bev_ssl, fd) < 0)
			goto err;
		break;
	default:
		goto err;
	}

	if (underlying) {
		bufferevent_setwatermark(underlying, EV_READ, 0, 0);
		bufferevent_enable(underlying, EV_READ|EV_WRITE);
		if (state == BUFFEREVENT_SSL_OPEN)
			bufferevent_suspend_read_(underlying,
			    BEV_SUSPEND_FILT_READ);
	} else {
		bev_ssl->bev.bev.enabled = EV_READ|EV_WRITE;
		if (bev_ssl->fd_is_set) {
			if (state != BUFFEREVENT_SSL_OPEN)
				if (event_add(&bev_ssl->bev.bev.ev_read, NULL) < 0)
					goto err;
			if (event_add(&bev_ssl->bev.bev.ev_write, NULL) < 0)
				goto err;
		}
	}

	return &bev_ssl->bev.bev;
err:
	if (bev_ssl)
		bufferevent_free(&bev_ssl->bev.bev);
	return NULL;
}