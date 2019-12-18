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
struct evhttp_connection {scalar_t__ state; int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 scalar_t__ EVCON_IDLE ; 
 scalar_t__ EVCON_WRITING ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 struct evhttp_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_connection_stop_detectclose (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_make_header (struct evhttp_connection*,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_write_buffer (struct evhttp_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_write_connectioncb ; 

__attribute__((used)) static void
evhttp_request_dispatch(struct evhttp_connection* evcon)
{
	struct evhttp_request *req = TAILQ_FIRST(&evcon->requests);

	/* this should not usually happy but it's possible */
	if (req == NULL)
		return;

	/* delete possible close detection events */
	evhttp_connection_stop_detectclose(evcon);

	/* we assume that the connection is connected already */
	EVUTIL_ASSERT(evcon->state == EVCON_IDLE);

	evcon->state = EVCON_WRITING;

	/* Create the header from the store arguments */
	evhttp_make_header(evcon, req);

	evhttp_write_buffer(evcon, evhttp_write_connectioncb, NULL);
}