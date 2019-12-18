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
struct evhttp_request {int flags; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (struct evhttp_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  output_headers; int /*<<< orphan*/  input_headers; int /*<<< orphan*/ * evcon; } ;
struct evhttp_connection {int flags; int /*<<< orphan*/  requests; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVCON_IDLE ; 
 int /*<<< orphan*/  EVCON_WRITING ; 
 int EVHTTP_CON_AUTOFREE ; 
 int EVHTTP_CON_OUTGOING ; 
 int EVHTTP_USER_OWNED ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connected (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_connect_ (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_reset_ (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_start_detectclose (struct evhttp_connection*) ; 
 scalar_t__ evhttp_is_connection_close (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_dispatch (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (struct evhttp_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_connection_done(struct evhttp_connection *evcon)
{
	struct evhttp_request *req = TAILQ_FIRST(&evcon->requests);
	int con_outgoing = evcon->flags & EVHTTP_CON_OUTGOING;
	int free_evcon = 0;

	if (con_outgoing) {
		/* idle or close the connection */
		int need_close;
		TAILQ_REMOVE(&evcon->requests, req, next);
		req->evcon = NULL;

		evcon->state = EVCON_IDLE;

		need_close =
		    evhttp_is_connection_close(req->flags, req->input_headers)||
		    evhttp_is_connection_close(req->flags, req->output_headers);

		/* check if we got asked to close the connection */
		if (need_close)
			evhttp_connection_reset_(evcon);

		if (TAILQ_FIRST(&evcon->requests) != NULL) {
			/*
			 * We have more requests; reset the connection
			 * and deal with the next request.
			 */
			if (!evhttp_connected(evcon))
				evhttp_connection_connect_(evcon);
			else
				evhttp_request_dispatch(evcon);
		} else if (!need_close) {
			/*
			 * The connection is going to be persistent, but we
			 * need to detect if the other side closes it.
			 */
			evhttp_connection_start_detectclose(evcon);
		} else if ((evcon->flags & EVHTTP_CON_AUTOFREE)) {
			/*
			 * If we have no more requests that need completion
			 * and we're not waiting for the connection to close
			 */
			 free_evcon = 1;
		}
	} else {
		/*
		 * incoming connection - we need to leave the request on the
		 * connection so that we can reply to it.
		 */
		evcon->state = EVCON_WRITING;
	}

	/* notify the user of the request */
	(*req->cb)(req, req->cb_arg);

	/* if this was an outgoing request, we own and it's done. so free it.
	 * unless the callback specifically requested to own the request.
	 */
	if (con_outgoing && ((req->flags & EVHTTP_USER_OWNED) == 0)) {
		evhttp_request_free(req);
	}

	/* If this was the last request of an outgoing connection and we're
	 * not waiting to receive a connection close event and we want to
	 * automatically free the connection. We check to ensure our request
	 * list is empty one last time just in case our callback added a
	 * new request.
	 */
	if (free_evcon && TAILQ_FIRST(&evcon->requests) == NULL) {
		evhttp_connection_free(evcon);
	}
}