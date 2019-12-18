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
struct server_request {scalar_t__ addrlen; int /*<<< orphan*/  addr; scalar_t__ response_len; int /*<<< orphan*/  response; } ;
struct evdns_server_port {int /*<<< orphan*/  event; int /*<<< orphan*/  socket; int /*<<< orphan*/  event_base; struct server_request* pending_replies; } ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_server_port*) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 scalar_t__ event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct evdns_server_port*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_socket_error_to_string (int) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,...) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_port_ready_callback ; 
 scalar_t__ server_request_free (struct server_request*) ; 

__attribute__((used)) static void
server_port_flush(struct evdns_server_port *port)
{
	struct server_request *req = port->pending_replies;
	ASSERT_LOCKED(port);
	while (req) {
		int r = sendto(port->socket, req->response, (int)req->response_len, 0,
			   (struct sockaddr*) &req->addr, (ev_socklen_t)req->addrlen);
		if (r < 0) {
			int err = evutil_socket_geterror(port->socket);
			if (EVUTIL_ERR_RW_RETRIABLE(err))
				return;
			log(EVDNS_LOG_WARN, "Error %s (%d) while writing response to port; dropping", evutil_socket_error_to_string(err), err);
		}
		if (server_request_free(req)) {
			/* we released the last reference to req->port. */
			return;
		} else {
			EVUTIL_ASSERT(req != port->pending_replies);
			req = port->pending_replies;
		}
	}

	/* We have no more pending requests; stop listening for 'writeable' events. */
	(void) event_del(&port->event);
	event_assign(&port->event, port->event_base,
				 port->socket, EV_READ | EV_PERSIST,
				 server_port_ready_callback, port);

	if (event_add(&port->event, NULL) < 0) {
		log(EVDNS_LOG_WARN, "Error from libevent when adding event for DNS server.");
		/* ???? Do more? */
	}
}