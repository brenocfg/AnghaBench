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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  evhttp_cancel_request (struct evhttp_request*) ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void
http_do_cancel(evutil_socket_t fd, short what, void *arg)
{
	struct evhttp_request *req = arg;
	evhttp_cancel_request(req);
	++test_ok;
}