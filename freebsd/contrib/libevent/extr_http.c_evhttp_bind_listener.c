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
struct evhttp_bound_socket {struct evconnlistener* listener; } ;
struct evhttp {int /*<<< orphan*/  sockets; } ;
struct evconnlistener {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evhttp_bound_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accept_socket_cb ; 
 int /*<<< orphan*/  evconnlistener_set_cb (struct evconnlistener*,int /*<<< orphan*/ ,struct evhttp*) ; 
 struct evhttp_bound_socket* mm_malloc (int) ; 
 int /*<<< orphan*/  next ; 

struct evhttp_bound_socket *
evhttp_bind_listener(struct evhttp *http, struct evconnlistener *listener)
{
	struct evhttp_bound_socket *bound;

	bound = mm_malloc(sizeof(struct evhttp_bound_socket));
	if (bound == NULL)
		return (NULL);

	bound->listener = listener;
	TAILQ_INSERT_TAIL(&http->sockets, bound, next);

	evconnlistener_set_cb(listener, accept_socket_cb, http);
	return bound;
}