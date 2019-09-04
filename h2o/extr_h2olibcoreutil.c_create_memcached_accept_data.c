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
struct timeval {int dummy; } ;
struct st_h2o_accept_data_t {int dummy; } ;
struct st_h2o_memcached_resumption_accept_data_t {struct st_h2o_accept_data_t super; int /*<<< orphan*/ * get_req; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_accept_ctx_t ;

/* Variables and functions */
 scalar_t__ create_accept_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_memcached_accept_timeout ; 

__attribute__((used)) static struct st_h2o_accept_data_t *create_memcached_accept_data(h2o_accept_ctx_t *ctx, h2o_socket_t *sock,
                                                                 struct timeval connected_at)
{
    struct st_h2o_memcached_resumption_accept_data_t *data = (struct st_h2o_memcached_resumption_accept_data_t *)create_accept_data(
        ctx, sock, connected_at, on_memcached_accept_timeout, sizeof(struct st_h2o_memcached_resumption_accept_data_t));
    data->get_req = NULL;
    return &data->super;
}