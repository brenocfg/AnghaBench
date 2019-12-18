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
struct evhttp_bound_socket {int /*<<< orphan*/  listener; } ;
struct evhttp {int /*<<< orphan*/  sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_bound_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evconnlistener_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct evhttp_bound_socket*) ; 
 int /*<<< orphan*/  next ; 

void
evhttp_del_accept_socket(struct evhttp *http, struct evhttp_bound_socket *bound)
{
	TAILQ_REMOVE(&http->sockets, bound, next);
	evconnlistener_free(bound->listener);
	mm_free(bound);
}