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
struct wm_context {struct bufferevent* bev; int /*<<< orphan*/  wm_high; scalar_t__ server; int /*<<< orphan*/  flags; } ;
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFEREVENT_SSL_ACCEPTING ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 struct bufferevent* bufferevent_openssl_socket_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wm_context*) ; 
 int /*<<< orphan*/  bufferevent_setwatermark (struct bufferevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evconnlistener_disable (struct evconnlistener*) ; 
 struct event_base* evconnlistener_get_base (struct evconnlistener*) ; 
 int /*<<< orphan*/  get_ssl_ctx () ; 
 int /*<<< orphan*/  the_cert ; 
 int /*<<< orphan*/  the_key ; 
 int /*<<< orphan*/  wm_eventcb ; 
 int /*<<< orphan*/  wm_transfer ; 

__attribute__((used)) static void
wm_acceptcb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *addr, int socklen, void *arg)
{
	struct wm_context *ctx = arg;
	struct bufferevent *bev;
	struct event_base *base = evconnlistener_get_base(listener);
	SSL *ssl = SSL_new(get_ssl_ctx());

	SSL_use_certificate(ssl, the_cert);
	SSL_use_PrivateKey(ssl, the_key);

	bev = bufferevent_openssl_socket_new(
		base, fd, ssl, BUFFEREVENT_SSL_ACCEPTING, ctx->flags);

	TT_BLATHER(("wm_transfer-%s(%p): accept",
		ctx->server ? "server" : "client", bev));

	bufferevent_setwatermark(bev, EV_READ, 0, ctx->wm_high);
	bufferevent_setcb(bev, wm_transfer, NULL, wm_eventcb, ctx);
	bufferevent_enable(bev, EV_READ|EV_WRITE);
	ctx->bev = bev;

	/* Only accept once, then disable ourself. */
	evconnlistener_disable(listener);
}