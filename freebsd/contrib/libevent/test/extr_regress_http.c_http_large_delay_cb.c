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
struct timeval {int tv_usec; } ;
struct evhttp_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVREQ_HTTP_EOF ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  delayed_client ; 
 int /*<<< orphan*/  event_base_once (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evhttp_request*,struct timeval*) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  http_delay_reply ; 

__attribute__((used)) static void
http_large_delay_cb(struct evhttp_request *req, void *arg)
{
	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_usec = 500000;

	event_base_once(arg, -1, EV_TIMEOUT, http_delay_reply, req, &tv);
	evhttp_connection_fail_(delayed_client, EVREQ_HTTP_EOF);
}