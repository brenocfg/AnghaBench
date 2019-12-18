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
struct st_redis_socket_data_t {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_socket_is_writing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_notify_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_write ; 

__attribute__((used)) static void socket_add_write(void *privdata)
{
    struct st_redis_socket_data_t *p = (struct st_redis_socket_data_t *)privdata;
    if (!h2o_socket_is_writing(p->socket)) {
        h2o_socket_notify_write(p->socket, on_write);
    }
}