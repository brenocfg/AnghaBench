#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; TYPE_2__* recycle_msg; } ;
typedef  TYPE_1__ MessageQueue ;
typedef  TYPE_2__ AVMessage ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  msg_free_res (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_queue_flush (TYPE_1__*) ; 

__attribute__((used)) inline static void msg_queue_destroy(MessageQueue *q)
{
    msg_queue_flush(q);

    SDL_LockMutex(q->mutex);
    while(q->recycle_msg) {
        AVMessage *msg = q->recycle_msg;
        if (msg)
            q->recycle_msg = msg->next;
        msg_free_res(msg);
        av_freep(&msg);
    }
    SDL_UnlockMutex(q->mutex);

    SDL_DestroyMutex(q->mutex);
    SDL_DestroyCond(q->cond);
}