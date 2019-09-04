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
struct TYPE_4__ {scalar_t__ started_count; int /*<<< orphan*/  notify; int /*<<< orphan*/  lock; struct TYPE_4__* queue; struct TYPE_4__* threads; } ;
typedef  TYPE_1__ IjkThreadPoolContext ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 

int ijk_threadpool_free(IjkThreadPoolContext *ctx)
{
    if(ctx == NULL || ctx->started_count > 0) {
        return -1;
    }

    /* Did we manage to allocate ? */
    if(ctx->threads) {
        free(ctx->threads);
        free(ctx->queue);

        /* Because we allocate pool->threads after initializing the
         mutex and condition variable, we're sure they're
         initialized. Let's lock the mutex just in case. */
        pthread_mutex_lock(&(ctx->lock));
        pthread_mutex_destroy(&(ctx->lock));
        pthread_cond_destroy(&(ctx->notify));
    }
    free(ctx);
    return 0;
}