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
struct TYPE_5__ {int /*<<< orphan*/  _link; int /*<<< orphan*/  _messages; TYPE_2__* queue; } ;
typedef  TYPE_1__ h2o_multithread_receiver_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ h2o_multithread_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void h2o_multithread_unregister_receiver(h2o_multithread_queue_t *queue, h2o_multithread_receiver_t *receiver)
{
    assert(queue == receiver->queue);
    assert(h2o_linklist_is_empty(&receiver->_messages));
    pthread_mutex_lock(&queue->mutex);
    h2o_linklist_unlink(&receiver->_link);
    pthread_mutex_unlock(&queue->mutex);
}