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
struct evhttp_request {struct evhttp_connection* evcon; } ;
struct evhttp_connection {int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVREQ_HTTP_REQUEST_CANCEL ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_free_auto (struct evhttp_request*) ; 
 int /*<<< orphan*/  next ; 

void
evhttp_cancel_request(struct evhttp_request *req)
{
	struct evhttp_connection *evcon = req->evcon;
	if (evcon != NULL) {
		/* We need to remove it from the connection */
		if (TAILQ_FIRST(&evcon->requests) == req) {
			/* it's currently being worked on, so reset
			 * the connection.
			 */
			evhttp_connection_fail_(evcon,
			    EVREQ_HTTP_REQUEST_CANCEL);

			/* connection fail freed the request */
			return;
		} else {
			/* otherwise, we can just remove it from the
			 * queue
			 */
			TAILQ_REMOVE(&evcon->requests, req, next);
		}
	}

	evhttp_request_free_auto(req);
}