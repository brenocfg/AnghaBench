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
struct st_h2o_sendfile_generator_t {int dummy; } ;
struct TYPE_3__ {scalar_t__* cb_arg; } ;
typedef  TYPE_1__ h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_addref_shared (struct st_h2o_sendfile_generator_t*) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (struct st_h2o_sendfile_generator_t*) ; 

__attribute__((used)) static void sendvec_update_refcnt(h2o_sendvec_t *vec, h2o_req_t *req, int is_incr)
{
    struct st_h2o_sendfile_generator_t *self = (void *)vec->cb_arg[0];

    if (is_incr) {
        h2o_mem_addref_shared(self);
    } else {
        h2o_mem_release_shared(self);
    }
}