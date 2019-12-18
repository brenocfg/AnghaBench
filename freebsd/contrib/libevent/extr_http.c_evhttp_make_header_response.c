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
struct evhttp_request {int major; int minor; int flags; int /*<<< orphan*/  output_headers; int /*<<< orphan*/  input_headers; int /*<<< orphan*/  output_buffer; int /*<<< orphan*/  response_code_line; int /*<<< orphan*/  response_code; } ;
struct evhttp_connection {TYPE_1__* http_server; int /*<<< orphan*/  bufev; } ;
struct TYPE_2__ {char* default_content_type; } ;

/* Variables and functions */
 int EVHTTP_PROXY_REQUEST ; 
 int /*<<< orphan*/  bufferevent_get_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add_printf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ evhttp_is_connection_close (int,int /*<<< orphan*/ ) ; 
 int evhttp_is_connection_keepalive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_maybe_add_content_length_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_maybe_add_date_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_remove_header (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ evhttp_response_needs_body (struct evhttp_request*) ; 

__attribute__((used)) static void
evhttp_make_header_response(struct evhttp_connection *evcon,
    struct evhttp_request *req)
{
	int is_keepalive = evhttp_is_connection_keepalive(req->input_headers);
	evbuffer_add_printf(bufferevent_get_output(evcon->bufev),
	    "HTTP/%d.%d %d %s\r\n",
	    req->major, req->minor, req->response_code,
	    req->response_code_line);

	if (req->major == 1) {
		if (req->minor >= 1)
			evhttp_maybe_add_date_header(req->output_headers);

		/*
		 * if the protocol is 1.0; and the connection was keep-alive
		 * we need to add a keep-alive header, too.
		 */
		if (req->minor == 0 && is_keepalive)
			evhttp_add_header(req->output_headers,
			    "Connection", "keep-alive");

		if ((req->minor >= 1 || is_keepalive) &&
		    evhttp_response_needs_body(req)) {
			/*
			 * we need to add the content length if the
			 * user did not give it, this is required for
			 * persistent connections to work.
			 */
			evhttp_maybe_add_content_length_header(
				req->output_headers,
				evbuffer_get_length(req->output_buffer));
		}
	}

	/* Potentially add headers for unidentified content. */
	if (evhttp_response_needs_body(req)) {
		if (evhttp_find_header(req->output_headers,
			"Content-Type") == NULL
		    && evcon->http_server->default_content_type) {
			evhttp_add_header(req->output_headers,
			    "Content-Type",
			    evcon->http_server->default_content_type);
		}
	}

	/* if the request asked for a close, we send a close, too */
	if (evhttp_is_connection_close(req->flags, req->input_headers)) {
		evhttp_remove_header(req->output_headers, "Connection");
		if (!(req->flags & EVHTTP_PROXY_REQUEST))
		    evhttp_add_header(req->output_headers, "Connection", "close");
		evhttp_remove_header(req->output_headers, "Proxy-Connection");
	}
}