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
struct event_base {int dummy; } ;
typedef  enum http_cancel_test_type { ____Placeholder_http_cancel_test_type } http_cancel_test_type ;

/* Variables and functions */
 int INACTIVE_SERVER ; 
 int NO_NS ; 
 int SERVER_TIMEOUT ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,struct event_base*) ; 
 int /*<<< orphan*/  http_failed_request_done ; 
 int /*<<< orphan*/  http_timed_out_request_done ; 

__attribute__((used)) static struct evhttp_request *
http_cancel_test_bad_request_new(enum http_cancel_test_type type,
	struct event_base *base)
{
#ifndef _WIN32
	if (!(type & NO_NS) && (type & SERVER_TIMEOUT))
		return evhttp_request_new(http_timed_out_request_done, base);
	else
#endif
	if ((type & INACTIVE_SERVER) || (type & NO_NS))
		return evhttp_request_new(http_failed_request_done, base);
	else
		return NULL;
}