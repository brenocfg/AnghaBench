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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct http_server {void (* cb ) (void*,struct http_request*) ;scalar_t__ fd; int port; void* cb_ctx; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ eloop_register_sock (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_server*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  http_server_cb ; 
 int /*<<< orphan*/  http_server_deinit (struct http_server*) ; 
 int inet_ntoa (struct in_addr) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 struct http_server* os_zalloc (int) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strerror (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

struct http_server * http_server_init(struct in_addr *addr, int port,
				      void (*cb)(void *ctx,
						 struct http_request *req),
				      void *cb_ctx)
{
	struct sockaddr_in sin;
	struct http_server *srv;
	int on = 1;

	srv = os_zalloc(sizeof(*srv));
	if (srv == NULL)
		return NULL;
	srv->cb = cb;
	srv->cb_ctx = cb_ctx;

	srv->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (srv->fd < 0)
		goto fail;

	if (setsockopt(srv->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		wpa_printf(MSG_DEBUG,
			   "HTTP: setsockopt(SO_REUSEADDR) failed: %s",
			   strerror(errno));
		/* try to continue anyway */
	}

	if (fcntl(srv->fd, F_SETFL, O_NONBLOCK) < 0)
		goto fail;
	if (port < 0)
		srv->port = 49152;
	else
		srv->port = port;

	os_memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = addr->s_addr;

	for (;;) {
		sin.sin_port = htons(srv->port);
		if (bind(srv->fd, (struct sockaddr *) &sin, sizeof(sin)) == 0)
			break;
		if (errno == EADDRINUSE) {
			/* search for unused port */
			if (++srv->port == 65535 || port >= 0)
				goto fail;
			continue;
		}
		wpa_printf(MSG_DEBUG, "HTTP: Failed to bind server port %d: "
			   "%s", srv->port, strerror(errno));
		goto fail;
	}
	if (listen(srv->fd, 10 /* max backlog */) < 0 ||
	    fcntl(srv->fd, F_SETFL, O_NONBLOCK) < 0 ||
	    eloop_register_sock(srv->fd, EVENT_TYPE_READ, http_server_cb,
				srv, NULL))
		goto fail;

	wpa_printf(MSG_DEBUG, "HTTP: Started server on %s:%d",
		   inet_ntoa(*addr), srv->port);

	return srv;

fail:
	http_server_deinit(srv);
	return NULL;
}