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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct terminate_state {int /*<<< orphan*/  base; struct evhttp_request* req; } ;
struct evhttp_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  HTTP_OK ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_connection_set_closecb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  evhttp_request_get_connection (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_reply_start (struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  terminate_chunked_close_cb ; 
 int /*<<< orphan*/  terminate_chunked_trickle_cb ; 

__attribute__((used)) static void
terminate_chunked_cb(struct evhttp_request *req, void *arg)
{
	struct terminate_state *state = arg;
	struct timeval tv;

	/* we want to know if this connection closes on us */
	evhttp_connection_set_closecb(
		evhttp_request_get_connection(req),
		terminate_chunked_close_cb, arg);

	state->req = req;

	evhttp_send_reply_start(req, HTTP_OK, "OK");

	tv.tv_sec = 0;
	tv.tv_usec = 3000;
	event_base_once(state->base, -1, EV_TIMEOUT, terminate_chunked_trickle_cb, arg, &tv);
}