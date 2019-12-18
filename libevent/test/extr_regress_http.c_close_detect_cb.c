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
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 scalar_t__ HTTP_OK ; 
 int /*<<< orphan*/  close_detect_launch ; 
 int /*<<< orphan*/  event_base_once (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evhttp_connection*,struct timeval*) ; 
 struct event_base* evhttp_connection_get_base (struct evhttp_connection*) ; 
 scalar_t__ evhttp_request_get_response_code (struct evhttp_request*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 

__attribute__((used)) static void
close_detect_cb(struct evhttp_request *req, void *arg)
{
	struct evhttp_connection *evcon = arg;
	struct event_base *base = evhttp_connection_get_base(evcon);
	struct timeval tv;

	if (req != NULL && evhttp_request_get_response_code(req) != HTTP_OK) {
		tt_abort_msg("Failed");
	}

	evutil_timerclear(&tv);
	tv.tv_sec = 0;   /* longer than the http time out */
	tv.tv_usec = 600000;   /* longer than the http time out */

	/* launch a new request on the persistent connection in .3 seconds */
	event_base_once(base, -1, EV_TIMEOUT, close_detect_launch, evcon, &tv);
 end:
	;
}