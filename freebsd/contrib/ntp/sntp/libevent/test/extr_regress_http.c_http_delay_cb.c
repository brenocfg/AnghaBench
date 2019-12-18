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

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  event_base_once (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evhttp_request*,struct timeval*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  http_delay_reply ; 

__attribute__((used)) static void
http_delay_cb(struct evhttp_request *req, void *arg)
{
	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = 0;
	tv.tv_usec = 200 * 1000;

	event_base_once(arg, -1, EV_TIMEOUT, http_delay_reply, req, &tv);
}