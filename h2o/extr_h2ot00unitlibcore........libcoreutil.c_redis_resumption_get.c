#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  cb; } ;
struct TYPE_25__ {TYPE_10__ timeout; TYPE_3__* ctx; } ;
struct st_h2o_redis_resumption_accept_data_t {TYPE_4__ super; int /*<<< orphan*/  get_command; } ;
struct TYPE_26__ {struct st_h2o_redis_resumption_accept_data_t* data; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_27__ {scalar_t__ state; } ;
typedef  TYPE_6__ h2o_redis_client_t ;
struct TYPE_28__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_7__ h2o_iovec_t ;
struct TYPE_24__ {TYPE_15__* ctx; } ;
struct TYPE_22__ {int /*<<< orphan*/  base; } ;
struct TYPE_23__ {int /*<<< orphan*/  port; TYPE_1__ host; int /*<<< orphan*/  prefix; } ;
struct TYPE_21__ {TYPE_2__ redis; } ;
struct TYPE_20__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CONNECTED ; 
 TYPE_18__ async_resumption_context ; 
 TYPE_7__ build_redis_key (TYPE_7__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_6__* get_redis_client (TYPE_15__*) ; 
 int /*<<< orphan*/  h2o_redis_command (TYPE_6__*,int /*<<< orphan*/ ,struct st_h2o_redis_resumption_accept_data_t*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_redis_connect (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_10__*) ; 
 int /*<<< orphan*/  on_redis_resumption_get_failed ; 
 int /*<<< orphan*/  redis_resumption_on_get ; 

__attribute__((used)) static void redis_resumption_get(h2o_socket_t *sock, h2o_iovec_t session_id)
{
    struct st_h2o_redis_resumption_accept_data_t *accept_data = sock->data;
    h2o_redis_client_t *client = get_redis_client(accept_data->super.ctx->ctx);

    if (client->state == H2O_REDIS_CONNECTION_STATE_CONNECTED) {
        h2o_iovec_t key = build_redis_key(session_id, async_resumption_context.redis.prefix);
        accept_data->get_command = h2o_redis_command(client, redis_resumption_on_get, accept_data, "GET %s", key.base);
        free(key.base);
    } else {
        if (client->state == H2O_REDIS_CONNECTION_STATE_CLOSED) {
            // try to connect
            h2o_redis_connect(client, async_resumption_context.redis.host.base, async_resumption_context.redis.port);
        }
        // abort resumption
        h2o_timer_unlink(&accept_data->super.timeout);
        accept_data->super.timeout.cb = on_redis_resumption_get_failed;
        h2o_timer_link(accept_data->super.ctx->ctx->loop, 0, &accept_data->super.timeout);
    }
}