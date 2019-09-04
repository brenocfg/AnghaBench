#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pending_count; int queue_size; int queue_tail; int /*<<< orphan*/  lock; int /*<<< orphan*/  notify; TYPE_1__* queue; scalar_t__ shutdown; } ;
struct TYPE_5__ {void* out_arg; void* in_arg; int /*<<< orphan*/ * function; } ;
typedef  int /*<<< orphan*/ * Runable ;
typedef  TYPE_1__ IjkThreadPoolTask ;
typedef  TYPE_2__ IjkThreadPoolContext ;

/* Variables and functions */
 int IJK_THREADPOOL_INVALID ; 
 int IJK_THREADPOOL_LOCK_FAILURE ; 
 int IJK_THREADPOOL_QUEUE_FULL ; 
 int IJK_THREADPOOL_SHUTDOWN ; 
 int MAX_QUEUE ; 
 scalar_t__ pthread_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 

int ijk_threadpool_add(IjkThreadPoolContext *ctx, Runable function,
                   void *in_arg, void *out_arg, int flags)
{
    int err = 0;
    int next;

    if(ctx == NULL || function == NULL) {
        return IJK_THREADPOOL_INVALID;
    }

    if(pthread_mutex_lock(&(ctx->lock)) != 0) {
        return IJK_THREADPOOL_LOCK_FAILURE;
    }

    if (ctx->pending_count == MAX_QUEUE || ctx->pending_count == ctx->queue_size) {
        pthread_mutex_unlock(&ctx->lock);
        return IJK_THREADPOOL_QUEUE_FULL;
    }

    if(ctx->pending_count == ctx->queue_size - 1) {
        int new_pueue_size = (ctx->queue_size * 2) > MAX_QUEUE ? MAX_QUEUE : (ctx->queue_size * 2);
        IjkThreadPoolTask *new_queue = (IjkThreadPoolTask *)realloc(ctx->queue, sizeof(IjkThreadPoolTask) * new_pueue_size);
        if (new_queue) {
            ctx->queue = new_queue;
            ctx->queue_size = new_pueue_size;
        }
    }

    next = (ctx->queue_tail + 1) % ctx->queue_size;
    do {
        /* Are we shutting down ? */
        if(ctx->shutdown) {
            err = IJK_THREADPOOL_SHUTDOWN;
            break;
        }

        /* Add task to queue */
        ctx->queue[ctx->queue_tail].function = function;
        ctx->queue[ctx->queue_tail].in_arg   = in_arg;
        ctx->queue[ctx->queue_tail].out_arg  = out_arg;
        ctx->queue_tail = next;
        ctx->pending_count += 1;

        /* pthread_cond_broadcast */
        if(pthread_cond_signal(&(ctx->notify)) != 0) {
            err = IJK_THREADPOOL_LOCK_FAILURE;
            break;
        }
    } while(0);

    if(pthread_mutex_unlock(&ctx->lock) != 0) {
        err = IJK_THREADPOOL_LOCK_FAILURE;
    }

    return err;
}