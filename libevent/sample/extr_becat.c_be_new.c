#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct event_base {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/  cert; int /*<<< orphan*/  ctx; } ;
struct context {TYPE_3__* opts; TYPE_2__ ssl; } ;
struct bufferevent {int dummy; } ;
typedef  int evutil_socket_t ;
typedef  enum bufferevent_ssl_state { ____Placeholder_bufferevent_ssl_state } bufferevent_ssl_state ;
struct TYPE_4__ {scalar_t__ ssl; } ;
struct TYPE_6__ {int max_read; TYPE_1__ extra; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int BUFFEREVENT_SSL_ACCEPTING ; 
 int BUFFEREVENT_SSL_CONNECTING ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int SSL_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bufferevent* bufferevent_openssl_socket_new (struct event_base*,int,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ bufferevent_set_max_single_read (struct bufferevent*,int) ; 
 struct bufferevent* bufferevent_socket_new (struct event_base*,int,int) ; 

__attribute__((used)) static struct bufferevent *
be_new(struct context *ctx, struct event_base *base, evutil_socket_t fd)
{
	SSL *ssl = NULL;
	struct bufferevent *bev = NULL;
	int flags = BEV_OPT_CLOSE_ON_FREE;
	enum bufferevent_ssl_state state = BUFFEREVENT_SSL_CONNECTING;

	if (fd != -1)
		state = BUFFEREVENT_SSL_ACCEPTING;

	if (ctx->opts->extra.ssl) {
		ssl = SSL_new(ctx->ssl.ctx);
		if (!ssl)
			goto err;
		if (SSL_use_certificate(ssl, ctx->ssl.cert) != 1)
			goto err;
		if (SSL_use_PrivateKey(ssl, ctx->ssl.pkey) != 1)
			goto err;
		bev = bufferevent_openssl_socket_new(base, fd, ssl, state, flags);
	} else {
		bev = bufferevent_socket_new(base, fd, flags);
	}
	if (ctx->opts->max_read != -1) {
		if (bufferevent_set_max_single_read(bev, ctx->opts->max_read))
			goto err;
	}
	return bev;
err:
	if (ssl)
		SSL_free(ssl);
	return NULL;
}