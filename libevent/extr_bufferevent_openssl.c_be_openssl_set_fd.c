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
struct bufferevent_openssl {int state; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  enum bufferevent_ssl_state { ____Placeholder_bufferevent_ssl_state } bufferevent_ssl_state ;

/* Variables and functions */
#define  BUFFEREVENT_SSL_ACCEPTING 130 
#define  BUFFEREVENT_SSL_CONNECTING 129 
#define  BUFFEREVENT_SSL_OPEN 128 
 int /*<<< orphan*/  SSL_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_handshake_callbacks (struct bufferevent_openssl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_open_callbacks (struct bufferevent_openssl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
be_openssl_set_fd(struct bufferevent_openssl *bev_ssl,
    enum bufferevent_ssl_state state, evutil_socket_t fd)
{
	bev_ssl->state = state;

	switch (state) {
	case BUFFEREVENT_SSL_ACCEPTING:
		if (!SSL_clear(bev_ssl->ssl))
			return -1;
		SSL_set_accept_state(bev_ssl->ssl);
		if (set_handshake_callbacks(bev_ssl, fd) < 0)
			return -1;
		break;
	case BUFFEREVENT_SSL_CONNECTING:
		if (!SSL_clear(bev_ssl->ssl))
			return -1;
		SSL_set_connect_state(bev_ssl->ssl);
		if (set_handshake_callbacks(bev_ssl, fd) < 0)
			return -1;
		break;
	case BUFFEREVENT_SSL_OPEN:
		if (set_open_callbacks(bev_ssl, fd) < 0)
			return -1;
		break;
	default:
		return -1;
	}

	return 0;
}