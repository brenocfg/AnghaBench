#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_redis_socket_data_t {TYPE_2__* context; int /*<<< orphan*/  socket; } ;
struct TYPE_3__ {int fd; } ;
struct TYPE_4__ {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_redis_socket_data_t*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_cleanup(void *privdata)
{
    struct st_redis_socket_data_t *p = (struct st_redis_socket_data_t *)privdata;
    h2o_socket_close(p->socket);
    p->context->c.fd = -1; /* prevent hiredis from closing fd twice */
    free(p);
}