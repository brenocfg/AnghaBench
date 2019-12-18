#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_5__ {int queue_size; int /*<<< orphan*/  started_count; int /*<<< orphan*/  thread_count; int /*<<< orphan*/ * threads; int /*<<< orphan*/ * queue; int /*<<< orphan*/  notify; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  IjkThreadPoolTask ;
typedef  TYPE_1__ IjkThreadPoolContext ;

/* Variables and functions */
 int MAX_QUEUE ; 
 int MAX_THREADS ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  ijk_threadpool_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijk_threadpool_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ijk_threadpool_thread ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

IjkThreadPoolContext *ijk_threadpool_create(int thread_count, int queue_size, int flags)
{
    IjkThreadPoolContext *ctx;
    int i;

    if(thread_count <= 0 || thread_count > MAX_THREADS || queue_size <= 0 || queue_size > MAX_QUEUE) {
        return NULL;
    }

    if((ctx = (IjkThreadPoolContext *)calloc(1, sizeof(IjkThreadPoolContext))) == NULL) {
        goto err;
    }

    ctx->queue_size = queue_size;

    /* Allocate thread and task queue */
    ctx->threads = (pthread_t *)calloc(1, sizeof(pthread_t) * thread_count);
    ctx->queue = (IjkThreadPoolTask *)calloc
        (queue_size, sizeof(IjkThreadPoolTask));

    /* Initialize mutex and conditional variable first */
    if((pthread_mutex_init(&(ctx->lock), NULL) != 0) ||
       (pthread_cond_init(&(ctx->notify), NULL) != 0) ||
       (ctx->threads == NULL) ||
       (ctx->queue == NULL)) {
        goto err;
    }

    /* Start worker threads */
    for(i = 0; i < thread_count; i++) {
        if(pthread_create(&(ctx->threads[i]), NULL,
                          ijk_threadpool_thread, (void*)ctx) != 0) {
            ijk_threadpool_destroy(ctx, 0);
            return NULL;
        }
        ctx->thread_count++;
        ctx->started_count++;
    }

    return ctx;

 err:
    if(ctx) {
        ijk_threadpool_free(ctx);
    }
    return NULL;
}