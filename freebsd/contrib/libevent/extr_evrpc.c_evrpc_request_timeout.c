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
struct evrpc_request_wrapper {struct evhttp_connection* evcon; } ;
struct evhttp_connection {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVREQ_HTTP_TIMEOUT ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evrpc_request_timeout(evutil_socket_t fd, short what, void *arg)
{
	struct evrpc_request_wrapper *ctx = arg;
	struct evhttp_connection *evcon = ctx->evcon;
	EVUTIL_ASSERT(evcon != NULL);

	evhttp_connection_fail_(evcon, EVREQ_HTTP_TIMEOUT);
}