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
struct evhttp_request {scalar_t__ kind; int chunked; int ntoread; TYPE_1__* evcon; int /*<<< orphan*/  input_headers; int /*<<< orphan*/  type; } ;
struct evhttp_connection {int /*<<< orphan*/  bufev; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  ev_uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_body_size; } ;

/* Variables and functions */
#define  CONTINUE 130 
 int /*<<< orphan*/  EVCON_READING_BODY ; 
 scalar_t__ EVHTTP_REQUEST ; 
 int /*<<< orphan*/  EVREQ_HTTP_INVALID_HEADER ; 
 int /*<<< orphan*/  EV_INT64_MAX ; 
 int /*<<< orphan*/  HTTP_EXPECTATIONFAILED ; 
#define  NO 129 
#define  OTHER 128 
 int /*<<< orphan*/  bufferevent_get_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_done (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 char* evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int evhttp_get_body_length (struct evhttp_request*) ; 
 int evhttp_have_expect (struct evhttp_request*,int) ; 
 int /*<<< orphan*/  evhttp_lingering_fail (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_method_may_have_body_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_read_body (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_continue (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_error (struct evhttp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ evutil_ascii_strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
evhttp_get_body(struct evhttp_connection *evcon, struct evhttp_request *req)
{
	const char *xfer_enc;

	/* If this is a request without a body, then we are done */
	if (req->kind == EVHTTP_REQUEST &&
	    !evhttp_method_may_have_body_(evcon, req->type)) {
		evhttp_connection_done(evcon);
		return;
	}
	evcon->state = EVCON_READING_BODY;
	xfer_enc = evhttp_find_header(req->input_headers, "Transfer-Encoding");
	if (xfer_enc != NULL && evutil_ascii_strcasecmp(xfer_enc, "chunked") == 0) {
		req->chunked = 1;
		req->ntoread = -1;
	} else {
		if (evhttp_get_body_length(req) == -1) {
			evhttp_connection_fail_(evcon, EVREQ_HTTP_INVALID_HEADER);
			return;
		}
		if (req->kind == EVHTTP_REQUEST && req->ntoread < 1) {
			/* An incoming request with no content-length and no
			 * transfer-encoding has no body. */
			evhttp_connection_done(evcon);
			return;
		}
	}

	/* Should we send a 100 Continue status line? */
	switch (evhttp_have_expect(req, 1)) {
		case CONTINUE:
				/* XXX It would be nice to do some sanity
				   checking here. Does the resource exist?
				   Should the resource accept post requests? If
				   no, we should respond with an error. For
				   now, just optimistically tell the client to
				   send their message body. */
				if (req->ntoread > 0) {
					/* ntoread is ev_int64_t, max_body_size is ev_uint64_t */ 
					if ((req->evcon->max_body_size <= EV_INT64_MAX) &&
						(ev_uint64_t)req->ntoread > req->evcon->max_body_size) {
						evhttp_lingering_fail(evcon, req);
						return;
					}
				}
				if (!evbuffer_get_length(bufferevent_get_input(evcon->bufev)))
					evhttp_send_continue(evcon, req);
			break;
		case OTHER:
			evhttp_send_error(req, HTTP_EXPECTATIONFAILED, NULL);
			return;
		case NO: break;
	}

	evhttp_read_body(evcon, req);
	/* note the request may have been freed in evhttp_read_body */
}