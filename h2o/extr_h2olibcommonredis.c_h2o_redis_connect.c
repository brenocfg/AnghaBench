#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {scalar_t__ err; TYPE_2__* data; } ;
typedef  TYPE_1__ redisAsyncContext ;
struct TYPE_10__ {scalar_t__ state; scalar_t__ connect_timeout; int /*<<< orphan*/  _timeout_entry; int /*<<< orphan*/  loop; TYPE_1__* _redis; } ;
typedef  TYPE_2__ h2o_redis_client_t ;

/* Variables and functions */
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CONNECTING ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  attach_loop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 int /*<<< orphan*/  h2o_redis_error_connection ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_connect ; 
 int /*<<< orphan*/  on_disconnect ; 
 TYPE_1__* redisAsyncConnect (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetConnectCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetDisconnectCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 

void h2o_redis_connect(h2o_redis_client_t *client, const char *host, uint16_t port)
{
    if (client->state != H2O_REDIS_CONNECTION_STATE_CLOSED) {
        return;
    }

    redisAsyncContext *redis = redisAsyncConnect(host, port);
    if (redis == NULL) {
        h2o_fatal("no memory");
    }

    client->_redis = redis;
    client->_redis->data = client;
    client->state = H2O_REDIS_CONNECTION_STATE_CONNECTING;

    attach_loop(redis, client->loop);
    redisAsyncSetConnectCallback(redis, on_connect);
    redisAsyncSetDisconnectCallback(redis, on_disconnect);

    if (redis->err != REDIS_OK) {
        /* some connection failures can be detected at this time */
        disconnect(client, h2o_redis_error_connection);
        return;
    }

    if (client->connect_timeout != 0)
        h2o_timer_link(client->loop, client->connect_timeout, &client->_timeout_entry);
}