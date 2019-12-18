#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ redisAsyncContext ;
typedef  int /*<<< orphan*/  h2o_redis_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  close_and_detach_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_error (TYPE_1__ const*) ; 

__attribute__((used)) static void on_disconnect(const redisAsyncContext *redis, int status)
{
    h2o_redis_client_t *client = (h2o_redis_client_t *)redis->data;
    if (client == NULL)
        return;

    close_and_detach_connection(client, get_error(redis));
}