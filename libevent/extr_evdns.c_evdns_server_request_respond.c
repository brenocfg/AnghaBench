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
struct server_request {struct server_request* next_pending; struct server_request* prev_pending; scalar_t__ addrlen; int /*<<< orphan*/  addr; scalar_t__ response_len; int /*<<< orphan*/  response; struct evdns_server_port* port; } ;
struct evdns_server_request {int dummy; } ;
struct evdns_server_port {int choked; struct server_request* pending_replies; int /*<<< orphan*/  event; scalar_t__ closing; int /*<<< orphan*/  socket; int /*<<< orphan*/  event_base; } ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_server_port*) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_server_port*) ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 struct server_request* TO_SERVER_REQUEST (struct evdns_server_request*) ; 
 int evdns_server_request_format_response (struct server_request*,int) ; 
 scalar_t__ event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct evdns_server_port*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_port_flush (struct evdns_server_port*) ; 
 int /*<<< orphan*/  server_port_ready_callback ; 
 scalar_t__ server_request_free (struct server_request*) ; 

int
evdns_server_request_respond(struct evdns_server_request *req_, int err)
{
	struct server_request *req = TO_SERVER_REQUEST(req_);
	struct evdns_server_port *port = req->port;
	int r = -1;

	EVDNS_LOCK(port);
	if (!req->response) {
		if ((r = evdns_server_request_format_response(req, err))<0)
			goto done;
	}

	r = sendto(port->socket, req->response, (int)req->response_len, 0,
			   (struct sockaddr*) &req->addr, (ev_socklen_t)req->addrlen);
	if (r<0) {
		int sock_err = evutil_socket_geterror(port->socket);
		if (EVUTIL_ERR_RW_RETRIABLE(sock_err))
			goto done;

		if (port->pending_replies) {
			req->prev_pending = port->pending_replies->prev_pending;
			req->next_pending = port->pending_replies;
			req->prev_pending->next_pending =
				req->next_pending->prev_pending = req;
		} else {
			req->prev_pending = req->next_pending = req;
			port->pending_replies = req;
			port->choked = 1;

			(void) event_del(&port->event);
			event_assign(&port->event, port->event_base, port->socket, (port->closing?0:EV_READ) | EV_WRITE | EV_PERSIST, server_port_ready_callback, port);

			if (event_add(&port->event, NULL) < 0) {
				log(EVDNS_LOG_WARN, "Error from libevent when adding event for DNS server");
			}

		}

		r = 1;
		goto done;
	}
	if (server_request_free(req)) {
		r = 0;
		goto done;
	}

	if (port->pending_replies)
		server_port_flush(port);

	r = 0;
done:
	EVDNS_UNLOCK(port);
	return r;
}