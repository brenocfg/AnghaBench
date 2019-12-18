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
struct terminate_state {struct terminate_state* base; int /*<<< orphan*/  req; } ;
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (struct terminate_state*) ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  event_base_loopexit (struct terminate_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_once (struct terminate_state*,int,int /*<<< orphan*/ ,void (*) (int /*<<< orphan*/ ,short,void*),void*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_request_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * evhttp_request_get_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_send_reply_chunk (int /*<<< orphan*/ ,struct evbuffer*) ; 
 int test_ok ; 

__attribute__((used)) static void
terminate_chunked_trickle_cb(evutil_socket_t fd, short events, void *arg)
{
	struct terminate_state *state = arg;
	struct evbuffer *evb;
	struct timeval tv;

	if (evhttp_request_get_connection(state->req) == NULL) {
		test_ok = 1;
		evhttp_request_free(state->req);
		event_base_loopexit(state->base,NULL);
		return;
	}

	evb = evbuffer_new();
	evbuffer_add_printf(evb, "%p", evb);
	evhttp_send_reply_chunk(state->req, evb);
	evbuffer_free(evb);

	tv.tv_sec = 0;
	tv.tv_usec = 3000;
	EVUTIL_ASSERT(state);
	EVUTIL_ASSERT(state->base);
	event_base_once(state->base, -1, EV_TIMEOUT, terminate_chunked_trickle_cb, arg, &tv);
}