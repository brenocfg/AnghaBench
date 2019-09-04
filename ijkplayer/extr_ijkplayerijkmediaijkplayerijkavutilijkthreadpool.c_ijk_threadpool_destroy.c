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
struct TYPE_4__ {int shutdown; int thread_count; int /*<<< orphan*/ * threads; int /*<<< orphan*/  lock; int /*<<< orphan*/  notify; } ;
typedef  TYPE_1__ IjkThreadPoolContext ;

/* Variables and functions */
 int IJK_THREADPOOL_INVALID ; 
 int IJK_THREADPOOL_LOCK_FAILURE ; 
 int IJK_THREADPOOL_SHUTDOWN ; 
 int IJK_THREADPOOL_THREAD_FAILURE ; 
 int ijk_threadpool_freep (TYPE_1__**) ; 
 scalar_t__ pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int ijk_threadpool_destroy(IjkThreadPoolContext *ctx, int flags)
{
    int i, err = 0;

    if(ctx == NULL) {
        return IJK_THREADPOOL_INVALID;
    }

    if(pthread_mutex_lock(&(ctx->lock)) != 0) {
        return IJK_THREADPOOL_LOCK_FAILURE;
    }

    do {
        /* Already shutting down */
        if(ctx->shutdown) {
            err = IJK_THREADPOOL_SHUTDOWN;
            break;
        }

        ctx->shutdown = flags;

        /* Wake up all worker threads */
        if((pthread_cond_broadcast(&(ctx->notify)) != 0) ||
           (pthread_mutex_unlock(&(ctx->lock)) != 0)) {
            err = IJK_THREADPOOL_LOCK_FAILURE;
            break;
        }

        /* Join all worker thread */
        for(i = 0; i < ctx->thread_count; i++) {
            if(pthread_join(ctx->threads[i], NULL) != 0) {
                err = IJK_THREADPOOL_THREAD_FAILURE;
            }
        }
    } while(0);

    /* Only if everything went well do we deallocate the pool */
    if(!err) {
        return ijk_threadpool_freep(&ctx);
    }
    return err;
}