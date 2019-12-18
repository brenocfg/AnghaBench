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
struct evhttp_request {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (struct evhttp_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * uri_elems; int /*<<< orphan*/ * uri; TYPE_1__* evcon; int /*<<< orphan*/  userdone; } ;
typedef  enum evhttp_request_error { ____Placeholder_evhttp_request_error } evhttp_request_error ;
struct TYPE_2__ {int /*<<< orphan*/  requests; } ;

/* Variables and functions */
#define  EVREQ_HTTP_BUFFER_ERROR 133 
#define  EVREQ_HTTP_DATA_TOO_LONG 132 
#define  EVREQ_HTTP_EOF 131 
#define  EVREQ_HTTP_INVALID_HEADER 130 
#define  EVREQ_HTTP_REQUEST_CANCEL 129 
#define  EVREQ_HTTP_TIMEOUT 128 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_uri_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (struct evhttp_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evhttp_connection_incoming_fail(struct evhttp_request *req,
    enum evhttp_request_error error)
{
	switch (error) {
	case EVREQ_HTTP_TIMEOUT:
	case EVREQ_HTTP_EOF:
		/*
		 * these are cases in which we probably should just
		 * close the connection and not send a reply.  this
		 * case may happen when a browser keeps a persistent
		 * connection open and we timeout on the read.  when
		 * the request is still being used for sending, we
		 * need to disassociated it from the connection here.
		 */
		if (!req->userdone) {
			/* remove it so that it will not be freed */
			TAILQ_REMOVE(&req->evcon->requests, req, next);
			/* indicate that this request no longer has a
			 * connection object
			 */
			req->evcon = NULL;
		}
		return (-1);
	case EVREQ_HTTP_INVALID_HEADER:
	case EVREQ_HTTP_BUFFER_ERROR:
	case EVREQ_HTTP_REQUEST_CANCEL:
	case EVREQ_HTTP_DATA_TOO_LONG:
	default:	/* xxx: probably should just error on default */
		/* the callback looks at the uri to determine errors */
		if (req->uri) {
			mm_free(req->uri);
			req->uri = NULL;
		}
		if (req->uri_elems) {
			evhttp_uri_free(req->uri_elems);
			req->uri_elems = NULL;
		}

		/*
		 * the callback needs to send a reply, once the reply has
		 * been send, the connection should get freed.
		 */
		(*req->cb)(req, req->cb_arg);
	}

	return (0);
}