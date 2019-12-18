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
struct evhttp_request {int /*<<< orphan*/  kind; } ;
struct evhttp_connection {scalar_t__ state; int /*<<< orphan*/  bufev; int /*<<< orphan*/  requests; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ EVCON_WRITING ; 
 int /*<<< orphan*/  EVHTTP_RESPONSE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct evbuffer* bufferevent_get_output (int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evhttp_start_read_ (struct evhttp_connection*) ; 

__attribute__((used)) static void
evhttp_write_connectioncb(struct evhttp_connection *evcon, void *arg)
{
	/* This is after writing the request to the server */
	struct evhttp_request *req = TAILQ_FIRST(&evcon->requests);
	struct evbuffer *output = bufferevent_get_output(evcon->bufev);
	EVUTIL_ASSERT(req != NULL);

	EVUTIL_ASSERT(evcon->state == EVCON_WRITING);

	/* We need to wait until we've written all of our output data before we can
	 * continue */
	if (evbuffer_get_length(output) > 0)
		return;

	/* We are done writing our header and are now expecting the response */
	req->kind = EVHTTP_RESPONSE;

	evhttp_start_read_(evcon);
}