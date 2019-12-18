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
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int fd; struct evhttp_connection* address; struct evhttp_connection* bind_address; int /*<<< orphan*/ * bufev; int /*<<< orphan*/  read_more_deferred_cb; int /*<<< orphan*/  retry_ev; struct evhttp* http_server; int /*<<< orphan*/  requests; int /*<<< orphan*/  closecb_arg; int /*<<< orphan*/  (* closecb ) (struct evhttp_connection*,int /*<<< orphan*/ ) ;} ;
struct evhttp {int /*<<< orphan*/  connections; } ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int /*<<< orphan*/  EVUTIL_SHUT_WR ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ *) ; 
 int bufferevent_get_options_ (int /*<<< orphan*/ *) ; 
 int bufferevent_getfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_debug_unassign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_deferred_cb_cancel_ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 scalar_t__ evhttp_connected (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_request_free_ (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evutil_closesocket (int) ; 
 int /*<<< orphan*/  get_deferred_queue (struct evhttp_connection*) ; 
 int /*<<< orphan*/  mm_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct evhttp_connection*,int /*<<< orphan*/ ) ; 

void
evhttp_connection_free(struct evhttp_connection *evcon)
{
	struct evhttp_request *req;
	int need_close = 0;

	/* notify interested parties that this connection is going down */
	if (evcon->fd != -1) {
		if (evhttp_connected(evcon) && evcon->closecb != NULL)
			(*evcon->closecb)(evcon, evcon->closecb_arg);
	}

	/* remove all requests that might be queued on this
	 * connection.  for server connections, this should be empty.
	 * because it gets dequeued either in evhttp_connection_done or
	 * evhttp_connection_fail_.
	 */
	while ((req = TAILQ_FIRST(&evcon->requests)) != NULL) {
		evhttp_request_free_(evcon, req);
	}

	if (evcon->http_server != NULL) {
		struct evhttp *http = evcon->http_server;
		TAILQ_REMOVE(&http->connections, evcon, next);
	}

	if (event_initialized(&evcon->retry_ev)) {
		event_del(&evcon->retry_ev);
		event_debug_unassign(&evcon->retry_ev);
	}

	event_deferred_cb_cancel_(get_deferred_queue(evcon),
	    &evcon->read_more_deferred_cb);

	if (evcon->bufev != NULL) {
		need_close =
			!(bufferevent_get_options_(evcon->bufev) & BEV_OPT_CLOSE_ON_FREE);
		if (evcon->fd == -1)
			evcon->fd = bufferevent_getfd(evcon->bufev);

		bufferevent_free(evcon->bufev);
	}

	if (evcon->fd != -1) {
		shutdown(evcon->fd, EVUTIL_SHUT_WR);
		if (need_close)
			evutil_closesocket(evcon->fd);
	}

	if (evcon->bind_address != NULL)
		mm_free(evcon->bind_address);

	if (evcon->address != NULL)
		mm_free(evcon->address);

	mm_free(evcon);
}