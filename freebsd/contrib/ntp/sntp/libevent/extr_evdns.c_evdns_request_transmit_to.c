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
struct sockaddr {int dummy; } ;
struct request {scalar_t__ request_len; int /*<<< orphan*/  ns; scalar_t__ request; TYPE_1__* base; } ;
struct nameserver {int requests_inflight; int /*<<< orphan*/  socket; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  address; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {scalar_t__ disable_when_inactive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  ASSERT_VALID_REQUEST (struct request*) ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 scalar_t__ event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_socket_error_to_string (int) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nameserver_failed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sendto (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evdns_request_transmit_to(struct request *req, struct nameserver *server) {
	int r;
	ASSERT_LOCKED(req->base);
	ASSERT_VALID_REQUEST(req);

	if (server->requests_inflight == 1 &&
		req->base->disable_when_inactive &&
		event_add(&server->event, NULL) < 0) {
		return 1;
	}

	r = sendto(server->socket, (void*)req->request, req->request_len, 0,
	    (struct sockaddr *)&server->address, server->addrlen);
	if (r < 0) {
		int err = evutil_socket_geterror(server->socket);
		if (EVUTIL_ERR_RW_RETRIABLE(err))
			return 1;
		nameserver_failed(req->ns, evutil_socket_error_to_string(err));
		return 2;
	} else if (r != (int)req->request_len) {
		return 1;  /* short write */
	} else {
		return 0;
	}
}