#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct st_redis_socket_data_t {char const* errstr; } ;
struct TYPE_7__ {struct st_redis_socket_data_t* data; } ;
struct TYPE_8__ {TYPE_1__ ev; } ;
typedef  TYPE_2__ redisAsyncContext ;
struct TYPE_9__ {scalar_t__ state; TYPE_2__* _redis; } ;
typedef  TYPE_3__ h2o_redis_client_t ;

/* Variables and functions */
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_and_detach_connection (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  redisAsyncFree (TYPE_2__*) ; 

__attribute__((used)) static void disconnect(h2o_redis_client_t *client, const char *errstr)
{
    assert(client->state != H2O_REDIS_CONNECTION_STATE_CLOSED);
    assert(client->_redis != NULL);

    redisAsyncContext *redis = client->_redis;
    struct st_redis_socket_data_t *data = redis->ev.data;
    data->errstr = errstr;
    close_and_detach_connection(client, errstr);
    redisAsyncFree(redis); /* immediately call all callbacks of pending commands with nil replies */
}