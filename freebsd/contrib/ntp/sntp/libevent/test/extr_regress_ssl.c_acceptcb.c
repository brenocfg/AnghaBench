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
struct sockaddr {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int BEV_OPT_DEFER_CALLBACKS ; 
 int /*<<< orphan*/  BUFFEREVENT_SSL_ACCEPTING ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 struct bufferevent* bufferevent_openssl_socket_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evconnlistener_disable (struct evconnlistener*) ; 
 int /*<<< orphan*/  eventcb ; 
 int /*<<< orphan*/  get_ssl_ctx () ; 
 int /*<<< orphan*/  getcert () ; 
 int /*<<< orphan*/  getkey () ; 
 int /*<<< orphan*/  respond_to_number ; 

__attribute__((used)) static void
acceptcb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *addr, int socklen, void *arg)
{
	struct basic_test_data *data = arg;
	struct bufferevent *bev;
	SSL *ssl = SSL_new(get_ssl_ctx());

	SSL_use_certificate(ssl, getcert());
	SSL_use_PrivateKey(ssl, getkey());

	bev = bufferevent_openssl_socket_new(
		data->base,
		fd,
		ssl,
		BUFFEREVENT_SSL_ACCEPTING,
		BEV_OPT_CLOSE_ON_FREE|BEV_OPT_DEFER_CALLBACKS);

	bufferevent_setcb(bev, respond_to_number, NULL, eventcb,
	    (void*)"server");

	bufferevent_enable(bev, EV_READ|EV_WRITE);

	/* Only accept once, then disable ourself. */
	evconnlistener_disable(listener);
}