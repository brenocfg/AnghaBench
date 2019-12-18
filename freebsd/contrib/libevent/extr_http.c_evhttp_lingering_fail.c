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
struct evhttp_connection {int flags; } ;

/* Variables and functions */
 int EVHTTP_CON_LINGERING_CLOSE ; 
 int /*<<< orphan*/  EVREQ_HTTP_DATA_TOO_LONG ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_lingering_close (struct evhttp_connection*,struct evhttp_request*) ; 

__attribute__((used)) static void
evhttp_lingering_fail(struct evhttp_connection *evcon,
	struct evhttp_request *req)
{
	if (evcon->flags & EVHTTP_CON_LINGERING_CLOSE)
		evhttp_lingering_close(evcon, req);
	else
		evhttp_connection_fail_(evcon, EVREQ_HTTP_DATA_TOO_LONG);
}