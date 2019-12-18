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
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {int recycle_count; int alloc_count; int /*<<< orphan*/  cond; int /*<<< orphan*/  nb_messages; TYPE_2__* last_msg; TYPE_2__* first_msg; TYPE_2__* recycle_msg; scalar_t__ abort_request; } ;
typedef  TYPE_1__ MessageQueue ;
typedef  TYPE_2__ AVMessage ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int) ; 
 TYPE_2__* av_malloc (int) ; 

__attribute__((used)) inline static int msg_queue_put_private(MessageQueue *q, AVMessage *msg)
{
    AVMessage *msg1;

    if (q->abort_request)
        return -1;

#ifdef FFP_MERGE
    msg1 = av_malloc(sizeof(AVMessage));
#else
    msg1 = q->recycle_msg;
    if (msg1) {
        q->recycle_msg = msg1->next;
        q->recycle_count++;
    } else {
        q->alloc_count++;
        msg1 = av_malloc(sizeof(AVMessage));
    }
#ifdef FFP_SHOW_MSG_RECYCLE
    int total_count = q->recycle_count + q->alloc_count;
    if (!(total_count % 10)) {
        av_log(NULL, AV_LOG_DEBUG, "msg-recycle \t%d + \t%d = \t%d\n", q->recycle_count, q->alloc_count, total_count);
    }
#endif
#endif
    if (!msg1)
        return -1;

    *msg1 = *msg;
    msg1->next = NULL;

    if (!q->last_msg)
        q->first_msg = msg1;
    else
        q->last_msg->next = msg1;
    q->last_msg = msg1;
    q->nb_messages++;
    SDL_CondSignal(q->cond);
    return 0;
}