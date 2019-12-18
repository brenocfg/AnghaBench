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
struct evhttp_request {void (* error_cb ) (int,void*) ;void (* cb ) (struct evhttp_request*,void*) ;void* cb_arg; } ;
struct evhttp_connection {int flags; int /*<<< orphan*/  requests; int /*<<< orphan*/  bufev; } ;
typedef  enum evhttp_request_error { ____Placeholder_evhttp_request_error } evhttp_request_error ;

/* Variables and functions */
 int EVHTTP_CON_INCOMING ; 
 int EVREQ_HTTP_REQUEST_CANCEL ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVUTIL_SET_SOCKET_ERROR (int const) ; 
 int EVUTIL_SOCKET_ERROR () ; 
 int EV_READ ; 
 int EV_WRITE ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_disable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evhttp_connection_connect_ (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int evhttp_connection_incoming_fail (struct evhttp_request*,int) ; 
 int /*<<< orphan*/  evhttp_connection_reset_ (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_request_free_ (struct evhttp_connection*,struct evhttp_request*) ; 
 void stub1 (struct evhttp_request*,void*) ; 

void
evhttp_connection_fail_(struct evhttp_connection *evcon,
    enum evhttp_request_error error)
{
	const int errsave = EVUTIL_SOCKET_ERROR();
	struct evhttp_request* req = TAILQ_FIRST(&evcon->requests);
	void (*cb)(struct evhttp_request *, void *);
	void *cb_arg;
	void (*error_cb)(enum evhttp_request_error, void *);
	void *error_cb_arg;
	EVUTIL_ASSERT(req != NULL);

	bufferevent_disable(evcon->bufev, EV_READ|EV_WRITE);

	if (evcon->flags & EVHTTP_CON_INCOMING) {
		/*
		 * for incoming requests, there are two different
		 * failure cases.  it's either a network level error
		 * or an http layer error. for problems on the network
		 * layer like timeouts we just drop the connections.
		 * For HTTP problems, we might have to send back a
		 * reply before the connection can be freed.
		 */
		if (evhttp_connection_incoming_fail(req, error) == -1)
			evhttp_connection_free(evcon);
		return;
	}

	error_cb = req->error_cb;
	error_cb_arg = req->cb_arg;
	/* when the request was canceled, the callback is not executed */
	if (error != EVREQ_HTTP_REQUEST_CANCEL) {
		/* save the callback for later; the cb might free our object */
		cb = req->cb;
		cb_arg = req->cb_arg;
	} else {
		cb = NULL;
		cb_arg = NULL;
	}

	/* do not fail all requests; the next request is going to get
	 * send over a new connection.   when a user cancels a request,
	 * all other pending requests should be processed as normal
	 */
	evhttp_request_free_(evcon, req);

	/* reset the connection */
	evhttp_connection_reset_(evcon);

	/* We are trying the next request that was queued on us */
	if (TAILQ_FIRST(&evcon->requests) != NULL)
		evhttp_connection_connect_(evcon);

	/* The call to evhttp_connection_reset_ overwrote errno.
	 * Let's restore the original errno, so that the user's
	 * callback can have a better idea of what the error was.
	 */
	EVUTIL_SET_SOCKET_ERROR(errsave);

	/* inform the user */
	if (error_cb != NULL)
		error_cb(error, error_cb_arg);
	if (cb != NULL)
		(*cb)(NULL, cb_arg);
}