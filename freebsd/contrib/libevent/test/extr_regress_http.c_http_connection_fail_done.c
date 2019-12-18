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
struct evhttp_connection {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 struct event_base* evhttp_connection_get_base (struct evhttp_connection*) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_connection_fail_done(struct evhttp_request *req, void *arg)
{
	struct evhttp_connection *evcon = arg;
	struct event_base *base = evhttp_connection_get_base(evcon);

	/* An ENETUNREACH error results in an unrecoverable
	 * evhttp_connection error (see evhttp_connection_fail_()).  The
	 * connection will be reset, and the user will be notified with a NULL
	 * req parameter. */
	tt_assert(!req);

	evhttp_connection_free(evcon);

	test_ok = 1;

 end:
	event_base_loopexit(base, NULL);
}