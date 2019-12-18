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
struct evhttp_request {scalar_t__ chunked; struct evhttp_connection* evcon; } ;
struct evhttp_connection {int /*<<< orphan*/  bufev; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 struct evbuffer* bufferevent_get_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_buffer (struct evbuffer*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,unsigned int) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evhttp_response_needs_body (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_write_buffer (struct evhttp_connection*,void (*) (struct evhttp_connection*,void*),void*) ; 

void
evhttp_send_reply_chunk_with_cb(struct evhttp_request *req, struct evbuffer *databuf,
    void (*cb)(struct evhttp_connection *, void *), void *arg)
{
	struct evhttp_connection *evcon = req->evcon;
	struct evbuffer *output;

	if (evcon == NULL)
		return;

	output = bufferevent_get_output(evcon->bufev);

	if (evbuffer_get_length(databuf) == 0)
		return;
	if (!evhttp_response_needs_body(req))
		return;
	if (req->chunked) {
		evbuffer_add_printf(output, "%x\r\n",
				    (unsigned)evbuffer_get_length(databuf));
	}
	evbuffer_add_buffer(output, databuf);
	if (req->chunked) {
		evbuffer_add(output, "\r\n", 2);
	}
	evhttp_write_buffer(evcon, cb, arg);
}