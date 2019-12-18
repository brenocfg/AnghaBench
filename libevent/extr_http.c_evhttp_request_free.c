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
struct evhttp_request {int flags; int /*<<< orphan*/ * output_buffer; int /*<<< orphan*/ * input_buffer; struct evhttp_request* output_headers; struct evhttp_request* input_headers; struct evhttp_request* host_cache; struct evhttp_request* response_code_line; int /*<<< orphan*/ * uri_elems; struct evhttp_request* uri; struct evhttp_request* remote_host; } ;

/* Variables and functions */
 int EVHTTP_REQ_DEFER_FREE ; 
 int EVHTTP_REQ_NEEDS_FREE ; 
 int /*<<< orphan*/  evbuffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_clear_headers (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_uri_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct evhttp_request*) ; 

void
evhttp_request_free(struct evhttp_request *req)
{
	if ((req->flags & EVHTTP_REQ_DEFER_FREE) != 0) {
		req->flags |= EVHTTP_REQ_NEEDS_FREE;
		return;
	}

	if (req->remote_host != NULL)
		mm_free(req->remote_host);
	if (req->uri != NULL)
		mm_free(req->uri);
	if (req->uri_elems != NULL)
		evhttp_uri_free(req->uri_elems);
	if (req->response_code_line != NULL)
		mm_free(req->response_code_line);
	if (req->host_cache != NULL)
		mm_free(req->host_cache);

	evhttp_clear_headers(req->input_headers);
	mm_free(req->input_headers);

	evhttp_clear_headers(req->output_headers);
	mm_free(req->output_headers);

	if (req->input_buffer != NULL)
		evbuffer_free(req->input_buffer);

	if (req->output_buffer != NULL)
		evbuffer_free(req->output_buffer);

	mm_free(req);
}