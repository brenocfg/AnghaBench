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
struct evrpc_pool {int timeout; struct event_base* base; int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  requests; int /*<<< orphan*/  connections; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct evrpc_pool* mm_calloc (int,int) ; 

struct evrpc_pool *
evrpc_pool_new(struct event_base *base)
{
	struct evrpc_pool *pool = mm_calloc(1, sizeof(struct evrpc_pool));
	if (pool == NULL)
		return (NULL);

	TAILQ_INIT(&pool->connections);
	TAILQ_INIT(&pool->requests);

	TAILQ_INIT(&pool->paused_requests);

	TAILQ_INIT(&pool->input_hooks);
	TAILQ_INIT(&pool->output_hooks);

	pool->base = base;
	pool->timeout = -1;

	return (pool);
}