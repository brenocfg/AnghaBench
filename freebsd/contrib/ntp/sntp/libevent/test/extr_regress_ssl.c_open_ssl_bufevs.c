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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int BUFFEREVENT_SSL_ACCEPTING ; 
 int BUFFEREVENT_SSL_CONNECTING ; 
 int BUFFEREVENT_SSL_OPEN ; 
 struct bufferevent* bufferevent_openssl_filter_new (struct event_base*,struct bufferevent*,int /*<<< orphan*/ *,int,int) ; 
 struct bufferevent* bufferevent_openssl_socket_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  done_writing_cb ; 
 int /*<<< orphan*/  eventcb ; 
 int /*<<< orphan*/  respond_to_number ; 

__attribute__((used)) static void
open_ssl_bufevs(struct bufferevent **bev1_out, struct bufferevent **bev2_out,
    struct event_base *base, int is_open, int flags, SSL *ssl1, SSL *ssl2,
    evutil_socket_t *fd_pair, struct bufferevent **underlying_pair)
{
	int state1 = is_open ? BUFFEREVENT_SSL_OPEN :BUFFEREVENT_SSL_CONNECTING;
	int state2 = is_open ? BUFFEREVENT_SSL_OPEN :BUFFEREVENT_SSL_ACCEPTING;
	if (fd_pair) {
		*bev1_out = bufferevent_openssl_socket_new(
			base, fd_pair[0], ssl1, state1, flags);
		*bev2_out = bufferevent_openssl_socket_new(
			base, fd_pair[1], ssl2, state2, flags);
	} else {
		*bev1_out = bufferevent_openssl_filter_new(
			base, underlying_pair[0], ssl1, state1, flags);
		*bev2_out = bufferevent_openssl_filter_new(
			base, underlying_pair[1], ssl2, state2, flags);

	}
	bufferevent_setcb(*bev1_out, respond_to_number, done_writing_cb,
	    eventcb, (void*)"client");
	bufferevent_setcb(*bev2_out, respond_to_number, done_writing_cb,
	    eventcb, (void*)"server");
}