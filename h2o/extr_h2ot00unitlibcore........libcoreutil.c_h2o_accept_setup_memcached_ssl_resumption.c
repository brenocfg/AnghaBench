#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_memcached_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  create; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctx; } ;
struct TYPE_5__ {unsigned int expiration; TYPE_1__ memcached; } ;

/* Variables and functions */
 TYPE_3__ accept_data_callbacks ; 
 TYPE_2__ async_resumption_context ; 
 int /*<<< orphan*/  create_memcached_accept_data ; 
 int /*<<< orphan*/  destroy_memcached_accept_data ; 
 int /*<<< orphan*/  h2o_socket_ssl_async_resumption_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcached_resumption_get ; 
 int /*<<< orphan*/  memcached_resumption_new ; 

void h2o_accept_setup_memcached_ssl_resumption(h2o_memcached_context_t *memc, unsigned expiration)
{
    async_resumption_context.memcached.ctx = memc;
    async_resumption_context.expiration = expiration;
    h2o_socket_ssl_async_resumption_init(memcached_resumption_get, memcached_resumption_new);
    accept_data_callbacks.create = create_memcached_accept_data;
    accept_data_callbacks.destroy = destroy_memcached_accept_data;
}