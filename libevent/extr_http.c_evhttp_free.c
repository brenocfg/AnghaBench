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
struct evhttp_server_alias {struct evhttp_server_alias* alias; int /*<<< orphan*/  aliases; struct evhttp_server_alias* vhost_pattern; int /*<<< orphan*/  virtualhosts; struct evhttp_server_alias* what; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  connections; int /*<<< orphan*/  listener; int /*<<< orphan*/  sockets; } ;
struct evhttp_connection {int dummy; } ;
struct evhttp_cb {struct evhttp_cb* alias; int /*<<< orphan*/  aliases; struct evhttp_cb* vhost_pattern; int /*<<< orphan*/  virtualhosts; struct evhttp_cb* what; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  connections; int /*<<< orphan*/  listener; int /*<<< orphan*/  sockets; } ;
struct evhttp_bound_socket {struct evhttp_bound_socket* alias; int /*<<< orphan*/  aliases; struct evhttp_bound_socket* vhost_pattern; int /*<<< orphan*/  virtualhosts; struct evhttp_bound_socket* what; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  connections; int /*<<< orphan*/  listener; int /*<<< orphan*/  sockets; } ;
struct evhttp {struct evhttp* alias; int /*<<< orphan*/  aliases; struct evhttp* vhost_pattern; int /*<<< orphan*/  virtualhosts; struct evhttp* what; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  connections; int /*<<< orphan*/  listener; int /*<<< orphan*/  sockets; } ;

/* Variables and functions */
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_server_alias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evconnlistener_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  mm_free (struct evhttp_server_alias*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  next_vhost ; 

void
evhttp_free(struct evhttp* http)
{
	struct evhttp_cb *http_cb;
	struct evhttp_connection *evcon;
	struct evhttp_bound_socket *bound;
	struct evhttp* vhost;
	struct evhttp_server_alias *alias;

	/* Remove the accepting part */
	while ((bound = TAILQ_FIRST(&http->sockets)) != NULL) {
		TAILQ_REMOVE(&http->sockets, bound, next);

		evconnlistener_free(bound->listener);

		mm_free(bound);
	}

	while ((evcon = TAILQ_FIRST(&http->connections)) != NULL) {
		/* evhttp_connection_free removes the connection */
		evhttp_connection_free(evcon);
	}

	while ((http_cb = TAILQ_FIRST(&http->callbacks)) != NULL) {
		TAILQ_REMOVE(&http->callbacks, http_cb, next);
		mm_free(http_cb->what);
		mm_free(http_cb);
	}

	while ((vhost = TAILQ_FIRST(&http->virtualhosts)) != NULL) {
		TAILQ_REMOVE(&http->virtualhosts, vhost, next_vhost);

		evhttp_free(vhost);
	}

	if (http->vhost_pattern != NULL)
		mm_free(http->vhost_pattern);

	while ((alias = TAILQ_FIRST(&http->aliases)) != NULL) {
		TAILQ_REMOVE(&http->aliases, alias, next);
		mm_free(alias->alias);
		mm_free(alias);
	}

	mm_free(http);
}