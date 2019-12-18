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
struct evrpc_pool {int /*<<< orphan*/  connections; } ;
struct evhttp_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
evrpc_pool_remove_connection(struct evrpc_pool *pool,
    struct evhttp_connection *connection)
{
	TAILQ_REMOVE(&pool->connections, connection, next);
}