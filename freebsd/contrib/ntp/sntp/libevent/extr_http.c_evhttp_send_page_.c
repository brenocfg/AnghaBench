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
struct evhttp_request {int major; int minor; scalar_t__ kind; int /*<<< orphan*/  output_headers; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ EVHTTP_RESPONSE ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  evhttp_clear_headers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_response_code_ (struct evhttp_request*,int,char*) ; 
 int /*<<< orphan*/  evhttp_send (struct evhttp_request*,struct evbuffer*) ; 

void
evhttp_send_page_(struct evhttp_request *req, struct evbuffer *databuf)
{
	if (!req->major || !req->minor) {
		req->major = 1;
		req->minor = 1;
	}

	if (req->kind != EVHTTP_RESPONSE)
		evhttp_response_code_(req, 200, "OK");

	evhttp_clear_headers(req->output_headers);
	evhttp_add_header(req->output_headers, "Content-Type", "text/html");
	evhttp_add_header(req->output_headers, "Connection", "close");

	evhttp_send(req, databuf);
}