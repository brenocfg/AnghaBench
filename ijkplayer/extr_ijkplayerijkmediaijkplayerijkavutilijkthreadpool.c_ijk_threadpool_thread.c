#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pending_count; scalar_t__ shutdown; size_t queue_head; int queue_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  started_count; TYPE_1__* queue; int /*<<< orphan*/  notify; } ;
struct TYPE_5__ {int /*<<< orphan*/  out_arg; int /*<<< orphan*/  in_arg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  out_arg; int /*<<< orphan*/  in_arg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ IjkThreadPoolTask ;
typedef  TYPE_3__ IjkThreadPoolContext ;

/* Variables and functions */
 scalar_t__ IJK_IMMEDIATE_SHUTDOWN ; 
 scalar_t__ IJK_LEISURELY_SHUTDOWN ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *ijk_threadpool_thread(void *pool_ctx)
{
    IjkThreadPoolContext *ctx = (IjkThreadPoolContext *)pool_ctx;
    IjkThreadPoolTask task;

    for(;;) {
        pthread_mutex_lock(&(ctx->lock));

        while((ctx->pending_count == 0) && (!ctx->shutdown)) {
            pthread_cond_wait(&(ctx->notify), &(ctx->lock));
        }

        if((ctx->shutdown == IJK_IMMEDIATE_SHUTDOWN) ||
           ((ctx->shutdown == IJK_LEISURELY_SHUTDOWN) &&
            (ctx->pending_count == 0))) {
               break;
           }

        /* Grab our task */
        task.function = ctx->queue[ctx->queue_head].function;
        task.in_arg   = ctx->queue[ctx->queue_head].in_arg;
        task.out_arg  = ctx->queue[ctx->queue_head].out_arg;
        ctx->queue_head = (ctx->queue_head + 1) % ctx->queue_size;
        ctx->pending_count -= 1;

        pthread_mutex_unlock(&(ctx->lock));

        (*(task.function))(task.in_arg, task.out_arg);
    }

    ctx->started_count--;

    pthread_mutex_unlock(&(ctx->lock));
    pthread_exit(NULL);
    return(NULL);
}