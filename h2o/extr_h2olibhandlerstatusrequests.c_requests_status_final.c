#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct st_requests_status_ctx_t* base; } ;
struct st_requests_status_ctx_t {int /*<<< orphan*/  mutex; TYPE_6__ req_data; int /*<<< orphan*/ * logconf; } ;
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_8__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  free (struct st_requests_status_ctx_t*) ; 
 TYPE_2__ h2o_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_logconf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static h2o_iovec_t requests_status_final(void *priv, h2o_globalconf_t *gconf, h2o_req_t *req)
{
    h2o_iovec_t ret = {NULL};
    struct st_requests_status_ctx_t *rsc = priv;

    if (rsc->logconf != NULL) {
        ret = h2o_concat(&req->pool, h2o_iovec_init(H2O_STRLIT(",\n \"requests\": [")), rsc->req_data,
                         h2o_iovec_init(H2O_STRLIT("\n ]")));
        h2o_logconf_dispose(rsc->logconf);
    }
    free(rsc->req_data.base);
    pthread_mutex_destroy(&rsc->mutex);

    free(rsc);
    return ret;
}