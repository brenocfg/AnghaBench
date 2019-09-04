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
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_read ; 

__attribute__((used)) static void socket_add_read(void *privdata)
{
    struct st_redis_socket_data_t *p = (struct st_redis_socket_data_t *)privdata;
    h2o_socket_read_start(p->socket, on_read);
}