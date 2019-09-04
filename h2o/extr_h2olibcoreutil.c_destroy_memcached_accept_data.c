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
struct st_h2o_memcached_resumption_accept_data_t {int /*<<< orphan*/  super; int /*<<< orphan*/ * get_req; } ;
struct st_h2o_accept_data_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_accept_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_memcached_accept_data(struct st_h2o_accept_data_t *_accept_data)
{
    struct st_h2o_memcached_resumption_accept_data_t *accept_data =
        (struct st_h2o_memcached_resumption_accept_data_t *)_accept_data;
    assert(accept_data->get_req == NULL);
    destroy_accept_data(&accept_data->super);
}