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
 int /*<<< orphan*/  HTTP_OK ; 
 int /*<<< orphan*/  evhttp_send_reply (struct evhttp_request*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void http_timeout_reply_cb(evutil_socket_t fd, short events, void *arg)
{
	struct evhttp_request *req = arg;
	evhttp_send_reply(req, HTTP_OK, "Everything is fine", NULL);
	test_ok++;
}