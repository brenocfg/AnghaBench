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
struct evhttp_request {scalar_t__ ntoread; size_t body_size; int flags; struct evbuffer* input_buffer; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* chunk_cb ) (struct evhttp_request*,int /*<<< orphan*/ ) ;TYPE_1__* evcon; scalar_t__ chunked; } ;
struct evhttp_connection {int /*<<< orphan*/  bufev; int /*<<< orphan*/  state; } ;
struct evbuffer {int dummy; } ;
struct TYPE_2__ {size_t max_body_size; } ;

/* Variables and functions */
#define  ALL_DATA_READ 132 
#define  DATA_CORRUPTED 131 
#define  DATA_TOO_LONG 130 
 int /*<<< orphan*/  EVCON_READING_TRAILER ; 
 int EVHTTP_REQ_DEFER_FREE ; 
 int EVHTTP_REQ_NEEDS_FREE ; 
 int /*<<< orphan*/  EVREQ_HTTP_DATA_TOO_LONG ; 
 int /*<<< orphan*/  EVREQ_HTTP_INVALID_HEADER ; 
 int /*<<< orphan*/  EV_READ ; 
#define  MORE_DATA_EXPECTED 129 
#define  REQUEST_CANCELED 128 
 int /*<<< orphan*/  bufferevent_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct evbuffer* bufferevent_get_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add_buffer (struct evbuffer*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 size_t evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_remove_buffer (struct evbuffer*,struct evbuffer*,size_t) ; 
 int /*<<< orphan*/  evhttp_connection_done (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int evhttp_handle_chunked_read (struct evhttp_request*,struct evbuffer*) ; 
 int /*<<< orphan*/  evhttp_lingering_fail (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_read_trailer (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_free_auto (struct evhttp_request*) ; 
 int /*<<< orphan*/  stub1 (struct evhttp_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_read_body(struct evhttp_connection *evcon, struct evhttp_request *req)
{
	struct evbuffer *buf = bufferevent_get_input(evcon->bufev);

	if (req->chunked) {
		switch (evhttp_handle_chunked_read(req, buf)) {
		case ALL_DATA_READ:
			/* finished last chunk */
			evcon->state = EVCON_READING_TRAILER;
			evhttp_read_trailer(evcon, req);
			return;
		case DATA_CORRUPTED:
		case DATA_TOO_LONG:
			/* corrupted data */
			evhttp_connection_fail_(evcon,
			    EVREQ_HTTP_DATA_TOO_LONG);
			return;
		case REQUEST_CANCELED:
			/* request canceled */
			evhttp_request_free_auto(req);
			return;
		case MORE_DATA_EXPECTED:
		default:
			break;
		}
	} else if (req->ntoread < 0) {
		/* Read until connection close. */
		if ((size_t)(req->body_size + evbuffer_get_length(buf)) < req->body_size) {
			evhttp_connection_fail_(evcon, EVREQ_HTTP_INVALID_HEADER);
			return;
		}

		req->body_size += evbuffer_get_length(buf);
		evbuffer_add_buffer(req->input_buffer, buf);
	} else if (req->chunk_cb != NULL || evbuffer_get_length(buf) >= (size_t)req->ntoread) {
		/* XXX: the above get_length comparison has to be fixed for overflow conditions! */
		/* We've postponed moving the data until now, but we're
		 * about to use it. */
		size_t n = evbuffer_get_length(buf);

		if (n > (size_t) req->ntoread)
			n = (size_t) req->ntoread;
		req->ntoread -= n;
		req->body_size += n;
		evbuffer_remove_buffer(buf, req->input_buffer, n);
	}

	if (req->body_size > req->evcon->max_body_size ||
	    (!req->chunked && req->ntoread >= 0 &&
		(size_t)req->ntoread > req->evcon->max_body_size)) {
		/* XXX: The above casted comparison must checked for overflow */
		/* failed body length test */

		evhttp_lingering_fail(evcon, req);
		return;
	}

	if (evbuffer_get_length(req->input_buffer) > 0 && req->chunk_cb != NULL) {
		req->flags |= EVHTTP_REQ_DEFER_FREE;
		(*req->chunk_cb)(req, req->cb_arg);
		req->flags &= ~EVHTTP_REQ_DEFER_FREE;
		evbuffer_drain(req->input_buffer,
		    evbuffer_get_length(req->input_buffer));
		if ((req->flags & EVHTTP_REQ_NEEDS_FREE) != 0) {
			evhttp_request_free_auto(req);
			return;
		}
	}

	if (!req->ntoread) {
		bufferevent_disable(evcon->bufev, EV_READ);
		/* Completed content length */
		evhttp_connection_done(evcon);
		return;
	}
}