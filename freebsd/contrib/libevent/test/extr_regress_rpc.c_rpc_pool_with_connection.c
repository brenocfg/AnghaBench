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
struct evrpc_pool {int dummy; } ;
struct evhttp_connection {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct evhttp_connection* evhttp_connection_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_pool_add_connection (struct evrpc_pool*,struct evhttp_connection*) ; 
 struct evrpc_pool* evrpc_pool_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct evrpc_pool *
rpc_pool_with_connection(ev_uint16_t port)
{
	struct evhttp_connection *evcon;
	struct evrpc_pool *pool;

	pool = evrpc_pool_new(NULL);
	assert(pool != NULL);

	evcon = evhttp_connection_new("127.0.0.1", port);
	assert(evcon != NULL);

	evrpc_pool_add_connection(pool, evcon);

	return (pool);
}