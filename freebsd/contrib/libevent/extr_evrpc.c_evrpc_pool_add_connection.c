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
struct evrpc_request_wrapper {int dummy; } ;
struct evrpc_pool {int /*<<< orphan*/  requests; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * base; int /*<<< orphan*/  connections; } ;
struct evhttp_connection {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * http_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 struct evrpc_request_wrapper* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evrpc_request_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_set_base (struct evhttp_connection*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_connection_set_timeout (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_schedule_request (struct evhttp_connection*,struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  evutil_timerisset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

void
evrpc_pool_add_connection(struct evrpc_pool *pool,
    struct evhttp_connection *connection)
{
	EVUTIL_ASSERT(connection->http_server == NULL);
	TAILQ_INSERT_TAIL(&pool->connections, connection, next);

	/*
	 * associate an event base with this connection
	 */
	if (pool->base != NULL)
		evhttp_connection_set_base(connection, pool->base);

	/*
	 * unless a timeout was specifically set for a connection,
	 * the connection inherits the timeout from the pool.
	 */
	if (!evutil_timerisset(&connection->timeout))
		evhttp_connection_set_timeout(connection, pool->timeout);

	/*
	 * if we have any requests pending, schedule them with the new
	 * connections.
	 */

	if (TAILQ_FIRST(&pool->requests) != NULL) {
		struct evrpc_request_wrapper *request =
		    TAILQ_FIRST(&pool->requests);
		TAILQ_REMOVE(&pool->requests, request, next);
		evrpc_schedule_request(connection, request);
	}
}