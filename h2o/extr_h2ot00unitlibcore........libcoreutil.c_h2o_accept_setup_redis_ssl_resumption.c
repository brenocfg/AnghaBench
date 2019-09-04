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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  create; } ;
struct TYPE_4__ {void* prefix; int /*<<< orphan*/  port; void* host; } ;
struct TYPE_5__ {unsigned int expiration; TYPE_1__ redis; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 TYPE_3__ accept_data_callbacks ; 
 TYPE_2__ async_resumption_context ; 
 int /*<<< orphan*/  create_redis_accept_data ; 
 int /*<<< orphan*/  destroy_redis_accept_data ; 
 int /*<<< orphan*/  h2o_socket_ssl_async_resumption_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_resumption_get ; 
 int /*<<< orphan*/  redis_resumption_new ; 

void h2o_accept_setup_redis_ssl_resumption(const char *host, uint16_t port, unsigned expiration, const char *prefix)
{
    async_resumption_context.redis.host = h2o_strdup(NULL, host, SIZE_MAX);
    async_resumption_context.redis.port = port;
    async_resumption_context.redis.prefix = h2o_strdup(NULL, prefix, SIZE_MAX);
    async_resumption_context.expiration = expiration;

    h2o_socket_ssl_async_resumption_init(redis_resumption_get, redis_resumption_new);

    accept_data_callbacks.create = create_redis_accept_data;
    accept_data_callbacks.destroy = destroy_redis_accept_data;
}