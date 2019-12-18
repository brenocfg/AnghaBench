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
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_OK ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,char*) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_output_headers (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_reply (struct evhttp_request*,int /*<<< orphan*/ ,char*,struct evbuffer*) ; 

__attribute__((used)) static void
http_badreq_cb(struct evhttp_request *req, void *arg)
{
	struct evbuffer *buf = evbuffer_new();

	evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/xml; charset=UTF-8");
	evbuffer_add_printf(buf, "Hello, %s!", "127.0.0.1");

	evhttp_send_reply(req, HTTP_OK, "OK", buf);
	evbuffer_free(buf);
}