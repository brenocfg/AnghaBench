#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__* ctx; } ;
struct st_h2o_redis_resumption_accept_data_t {TYPE_1__ super; } ;
struct TYPE_24__ {struct st_h2o_redis_resumption_accept_data_t* data; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_25__ {scalar_t__ state; } ;
typedef  TYPE_6__ h2o_redis_client_t ;
struct TYPE_26__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_7__ h2o_iovec_t ;
struct TYPE_23__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_21__ {int /*<<< orphan*/  base; } ;
struct TYPE_22__ {int /*<<< orphan*/  prefix; int /*<<< orphan*/  port; TYPE_2__ host; } ;
struct TYPE_19__ {int expiration; TYPE_3__ redis; } ;

/* Variables and functions */
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 TYPE_18__ async_resumption_context ; 
 TYPE_7__ build_redis_key (TYPE_7__,int /*<<< orphan*/ ) ; 
 TYPE_7__ build_redis_value (TYPE_7__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_6__* get_redis_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_redis_command (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_redis_connect (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void redis_resumption_new(h2o_socket_t *sock, h2o_iovec_t session_id, h2o_iovec_t session_data)
{
    struct st_h2o_redis_resumption_accept_data_t *accept_data = sock->data;
    h2o_redis_client_t *client = get_redis_client(accept_data->super.ctx->ctx);

    if (client->state == H2O_REDIS_CONNECTION_STATE_CLOSED) {
        // try to connect
        h2o_redis_connect(client, async_resumption_context.redis.host.base, async_resumption_context.redis.port);
    }

    h2o_iovec_t key = build_redis_key(session_id, async_resumption_context.redis.prefix);
    h2o_iovec_t value = build_redis_value(session_data);
    h2o_redis_command(client, NULL, NULL, "SETEX %s %d %s", key.base, async_resumption_context.expiration * 10, value.base);
    free(key.base);
    free(value.base);
}