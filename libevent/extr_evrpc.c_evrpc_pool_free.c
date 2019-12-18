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
struct evrpc_request_wrapper {int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  connections; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  requests; } ;
struct evrpc_pool {int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  connections; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  requests; } ;
struct evrpc_hook_ctx {int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  connections; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  requests; } ;
struct evrpc_hook {int dummy; } ;
struct evhttp_connection {int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  connections; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_INPUT ; 
 int /*<<< orphan*/  EVRPC_OUTPUT ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evrpc_request_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evrpc_request_wrapper*) ; 
 int evrpc_remove_hook (struct evrpc_request_wrapper*,int /*<<< orphan*/ ,struct evrpc_hook*) ; 
 int /*<<< orphan*/  evrpc_request_wrapper_free (struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  mm_free (struct evrpc_request_wrapper*) ; 
 int /*<<< orphan*/  next ; 

void
evrpc_pool_free(struct evrpc_pool *pool)
{
	struct evhttp_connection *connection;
	struct evrpc_request_wrapper *request;
	struct evrpc_hook_ctx *pause;
	struct evrpc_hook *hook;
	int r;

	while ((request = TAILQ_FIRST(&pool->requests)) != NULL) {
		TAILQ_REMOVE(&pool->requests, request, next);
		evrpc_request_wrapper_free(request);
	}

	while ((pause = TAILQ_FIRST(&pool->paused_requests)) != NULL) {
		TAILQ_REMOVE(&pool->paused_requests, pause, next);
		mm_free(pause);
	}

	while ((connection = TAILQ_FIRST(&pool->connections)) != NULL) {
		TAILQ_REMOVE(&pool->connections, connection, next);
		evhttp_connection_free(connection);
	}

	while ((hook = TAILQ_FIRST(&pool->input_hooks)) != NULL) {
		r = evrpc_remove_hook(pool, EVRPC_INPUT, hook);
		EVUTIL_ASSERT(r);
	}

	while ((hook = TAILQ_FIRST(&pool->output_hooks)) != NULL) {
		r = evrpc_remove_hook(pool, EVRPC_OUTPUT, hook);
		EVUTIL_ASSERT(r);
	}

	mm_free(pool);
}