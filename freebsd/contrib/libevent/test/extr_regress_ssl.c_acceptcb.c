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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct sockaddr {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; scalar_t__ setup_data; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  enum regress_openssl_type { ____Placeholder_regress_openssl_type } regress_openssl_type ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int BEV_OPT_DEFER_CALLBACKS ; 
 int /*<<< orphan*/  BUFFEREVENT_SSL_ACCEPTING ; 
 int EV_READ ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int EV_WRITE ; 
 scalar_t__ REGRESS_OPENSSL_SERVER ; 
 int REGRESS_OPENSSL_SLEEP ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acceptcb_deferred ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 struct bufferevent* bufferevent_openssl_socket_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evconnlistener_disable (struct evconnlistener*) ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*,struct timeval*) ; 
 int /*<<< orphan*/  eventcb ; 
 int /*<<< orphan*/  get_ssl_ctx () ; 
 int /*<<< orphan*/  respond_to_number ; 
 int /*<<< orphan*/  ssl_getcert () ; 
 int /*<<< orphan*/  ssl_getkey () ; 

__attribute__((used)) static void
acceptcb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *addr, int socklen, void *arg)
{
	struct basic_test_data *data = arg;
	struct bufferevent *bev;
	enum regress_openssl_type type;
	SSL *ssl = SSL_new(get_ssl_ctx());

	type = (enum regress_openssl_type)data->setup_data;

	SSL_use_certificate(ssl, ssl_getcert());
	SSL_use_PrivateKey(ssl, ssl_getkey());

	bev = bufferevent_openssl_socket_new(
		data->base,
		fd,
		ssl,
		BUFFEREVENT_SSL_ACCEPTING,
		BEV_OPT_CLOSE_ON_FREE|BEV_OPT_DEFER_CALLBACKS);

	bufferevent_setcb(bev, respond_to_number, NULL, eventcb,
	    (void*)(REGRESS_OPENSSL_SERVER));

	if (type & REGRESS_OPENSSL_SLEEP) {
		struct timeval when = { 1, 0 };
		event_base_once(data->base, -1, EV_TIMEOUT,
		    acceptcb_deferred, bev, &when);
		bufferevent_disable(bev, EV_READ|EV_WRITE);
	} else {
		bufferevent_enable(bev, EV_READ|EV_WRITE);
	}

	/* Only accept once, then disable ourself. */
	evconnlistener_disable(listener);
}