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
struct evhttp_request {int userdone; int /*<<< orphan*/  output_buffer; struct evhttp_connection* evcon; } ;
struct evhttp_connection {int /*<<< orphan*/  requests; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evbuffer_add_buffer (int /*<<< orphan*/ ,struct evbuffer*) ; 
 int /*<<< orphan*/  evhttp_make_header (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_done ; 
 int /*<<< orphan*/  evhttp_write_buffer (struct evhttp_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
evhttp_send(struct evhttp_request *req, struct evbuffer *databuf)
{
	struct evhttp_connection *evcon = req->evcon;

	if (evcon == NULL) {
		evhttp_request_free(req);
		return;
	}

	EVUTIL_ASSERT(TAILQ_FIRST(&evcon->requests) == req);

	/* we expect no more calls form the user on this request */
	req->userdone = 1;

	/* xxx: not sure if we really should expose the data buffer this way */
	if (databuf != NULL)
		evbuffer_add_buffer(req->output_buffer, databuf);

	/* Adds headers to the response */
	evhttp_make_header(evcon, req);

	evhttp_write_buffer(evcon, evhttp_send_done, NULL);
}