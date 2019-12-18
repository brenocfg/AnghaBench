#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char uint64_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_10__ {TYPE_2__* queue; int /*<<< orphan*/  _messages; int /*<<< orphan*/  _link; } ;
typedef  TYPE_3__ h2o_multithread_receiver_t ;
struct TYPE_11__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_4__ h2o_multithread_message_t ;
struct TYPE_12__ {int /*<<< orphan*/  write; } ;
struct TYPE_8__ {int /*<<< orphan*/  active; } ;
struct TYPE_9__ {TYPE_5__ async; int /*<<< orphan*/  mutex; TYPE_1__ receivers; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_async_send (TYPE_5__*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void h2o_multithread_send_message(h2o_multithread_receiver_t *receiver, h2o_multithread_message_t *message)
{
    int do_send = 0;

    pthread_mutex_lock(&receiver->queue->mutex);
    if (message != NULL) {
        assert(!h2o_linklist_is_linked(&message->link));
        if (h2o_linklist_is_empty(&receiver->_messages)) {
            h2o_linklist_unlink(&receiver->_link);
            h2o_linklist_insert(&receiver->queue->receivers.active, &receiver->_link);
            do_send = 1;
        }
        h2o_linklist_insert(&receiver->_messages, &message->link);
    } else {
        if (h2o_linklist_is_empty(&receiver->_messages))
            do_send = 1;
    }
    pthread_mutex_unlock(&receiver->queue->mutex);

    if (do_send) {
#if H2O_USE_LIBUV
        uv_async_send(&receiver->queue->async);
#else
#ifdef __linux__
        uint64_t tmp = 1;
        while (write(receiver->queue->async.write, &tmp, sizeof(tmp)) == -1 && errno == EINTR)
#else
        while (write(receiver->queue->async.write, "", 1) == -1 && errno == EINTR)
#endif
            ;
#endif
    }
}