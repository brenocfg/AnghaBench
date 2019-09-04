#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_redis_socket_data_t {int /*<<< orphan*/  context; } ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  redisAsyncHandleWrite (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_write(h2o_socket_t *sock, const char *err)
{
    struct st_redis_socket_data_t *p = (struct st_redis_socket_data_t *)sock->data;
    redisAsyncHandleWrite(p->context);
}