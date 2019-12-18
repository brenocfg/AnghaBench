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
typedef  enum evhttp_request_error { ____Placeholder_evhttp_request_error } evhttp_request_error ;

/* Variables and functions */
 int EVREQ_HTTP_REQUEST_CANCEL ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int test_ok ; 

__attribute__((used)) static void
http_request_error_cb_with_cancel(enum evhttp_request_error error, void *arg)
{
	if (error != EVREQ_HTTP_REQUEST_CANCEL) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}
	test_ok = 1;

	{
		struct timeval tv;
		evutil_timerclear(&tv);
		tv.tv_sec = 0;
		tv.tv_usec = 500 * 1000;
		event_base_loopexit(exit_base, &tv);
	}
}