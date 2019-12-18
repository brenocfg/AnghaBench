#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pending; } ;
typedef  TYPE_1__ h2o_memcached_req_t ;
struct TYPE_7__ {scalar_t__ num_threads_connected; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  pending; } ;
typedef  TYPE_2__ h2o_memcached_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  discard_req (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispatch(h2o_memcached_context_t *ctx, h2o_memcached_req_t *req)
{
    pthread_mutex_lock(&ctx->mutex);

    if (ctx->num_threads_connected != 0) {
        h2o_linklist_insert(&ctx->pending, &req->pending);
        pthread_cond_signal(&ctx->cond);
    } else {
        discard_req(req);
    }

    pthread_mutex_unlock(&ctx->mutex);
}