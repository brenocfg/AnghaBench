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
struct evhttp_request {int chunked; int /*<<< orphan*/  evcon; int /*<<< orphan*/  output_headers; } ;

/* Variables and functions */
 scalar_t__ REQ_VERSION_ATLEAST (struct evhttp_request*,int,int) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_make_header (int /*<<< orphan*/ ,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_response_code_ (struct evhttp_request*,int,char const*) ; 
 scalar_t__ evhttp_response_needs_body (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_write_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
evhttp_send_reply_start(struct evhttp_request *req, int code,
    const char *reason)
{
	evhttp_response_code_(req, code, reason);
	if (evhttp_find_header(req->output_headers, "Content-Length") == NULL &&
	    REQ_VERSION_ATLEAST(req, 1, 1) &&
	    evhttp_response_needs_body(req)) {
		/*
		 * prefer HTTP/1.1 chunked encoding to closing the connection;
		 * note RFC 2616 section 4.4 forbids it with Content-Length:
		 * and it's not necessary then anyway.
		 */
		evhttp_add_header(req->output_headers, "Transfer-Encoding",
		    "chunked");
		req->chunked = 1;
	} else {
		req->chunked = 0;
	}
	evhttp_make_header(req->evcon, req);
	evhttp_write_buffer(req->evcon, NULL, NULL);
}