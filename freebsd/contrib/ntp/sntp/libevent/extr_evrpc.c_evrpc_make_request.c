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
struct evrpc_request_wrapper {int /*<<< orphan*/  ev_timeout; struct evrpc_pool* pool; } ;
struct evrpc_pool {int /*<<< orphan*/  requests; int /*<<< orphan*/  connections; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evrpc_request_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_pool_schedule (struct evrpc_pool*) ; 
 int /*<<< orphan*/  evrpc_request_timeout ; 
 int /*<<< orphan*/  evtimer_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  next ; 

int
evrpc_make_request(struct evrpc_request_wrapper *ctx)
{
	struct evrpc_pool *pool = ctx->pool;

	/* initialize the event structure for this rpc */
	evtimer_assign(&ctx->ev_timeout, pool->base, evrpc_request_timeout, ctx);

	/* we better have some available connections on the pool */
	EVUTIL_ASSERT(TAILQ_FIRST(&pool->connections) != NULL);

	/*
	 * if no connection is available, we queue the request on the pool,
	 * the next time a connection is empty, the rpc will be send on that.
	 */
	TAILQ_INSERT_TAIL(&pool->requests, ctx, next);

	evrpc_pool_schedule(pool);

	return (0);
}