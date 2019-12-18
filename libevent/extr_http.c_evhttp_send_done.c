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
struct evhttp_request {int flags; int /*<<< orphan*/  input_headers; int /*<<< orphan*/  on_complete_cb_arg; int /*<<< orphan*/  (* on_complete_cb ) (struct evhttp_request*,int /*<<< orphan*/ ) ;} ;
struct evhttp_connection {int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int EVHTTP_REQ_OWN_CONNECTION ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ REQ_VERSION_BEFORE (struct evhttp_request*,int,int) ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int evhttp_associate_new_request_with_connection (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_is_connection_keepalive (int /*<<< orphan*/ ) ; 
 scalar_t__ evhttp_is_request_connection_close (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (struct evhttp_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_send_done(struct evhttp_connection *evcon, void *arg)
{
	int need_close;
	struct evhttp_request *req = TAILQ_FIRST(&evcon->requests);
	TAILQ_REMOVE(&evcon->requests, req, next);

	if (req->on_complete_cb != NULL) {
		req->on_complete_cb(req, req->on_complete_cb_arg);
	}

	need_close =
	    (REQ_VERSION_BEFORE(req, 1, 1) &&
	    !evhttp_is_connection_keepalive(req->input_headers)) ||
	    evhttp_is_request_connection_close(req);

	EVUTIL_ASSERT(req->flags & EVHTTP_REQ_OWN_CONNECTION);
	evhttp_request_free(req);

	if (need_close) {
		evhttp_connection_free(evcon);
		return;
	}

	/* we have a persistent connection; try to accept another request. */
	if (evhttp_associate_new_request_with_connection(evcon) == -1) {
		evhttp_connection_free(evcon);
	}
}