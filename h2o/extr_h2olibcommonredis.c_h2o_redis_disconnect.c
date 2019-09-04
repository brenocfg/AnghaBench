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
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ h2o_redis_client_t ;

/* Variables and functions */
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 int /*<<< orphan*/  disconnect (TYPE_1__*,int /*<<< orphan*/ *) ; 

void h2o_redis_disconnect(h2o_redis_client_t *client)
{
    if (client->state != H2O_REDIS_CONNECTION_STATE_CLOSED)
        disconnect(client, NULL);
}