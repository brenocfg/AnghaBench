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
struct evhttp_request {int userdone; scalar_t__ chunked; struct evhttp_connection* evcon; } ;
struct evhttp_connection {int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/  (* cb ) (struct evhttp_connection*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  bufev; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 struct evbuffer* bufferevent_get_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_done (struct evhttp_connection*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_write_buffer (struct evhttp_connection*,int /*<<< orphan*/  (*) (struct evhttp_connection*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

void
evhttp_send_reply_end(struct evhttp_request *req)
{
	struct evhttp_connection *evcon = req->evcon;
	struct evbuffer *output;

	if (evcon == NULL) {
		evhttp_request_free(req);
		return;
	}

	output = bufferevent_get_output(evcon->bufev);

	/* we expect no more calls form the user on this request */
	req->userdone = 1;

	if (req->chunked) {
		evbuffer_add(output, "0\r\n\r\n", 5);
		evhttp_write_buffer(req->evcon, evhttp_send_done, NULL);
		req->chunked = 0;
	} else if (evbuffer_get_length(output) == 0) {
		/* let the connection know that we are done with the request */
		evhttp_send_done(evcon, NULL);
	} else {
		/* make the callback execute after all data has been written */
		evcon->cb = evhttp_send_done;
		evcon->cb_arg = NULL;
	}
}