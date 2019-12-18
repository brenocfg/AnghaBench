#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_6__ {int /*<<< orphan*/  inactive; int /*<<< orphan*/  active; } ;
struct TYPE_8__ {TYPE_2__ async; int /*<<< orphan*/  mutex; TYPE_1__ receivers; } ;
typedef  TYPE_3__ h2o_multithread_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libuv_destroy_delayed ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void h2o_multithread_destroy_queue(h2o_multithread_queue_t *queue)
{
    assert(h2o_linklist_is_empty(&queue->receivers.active));
    assert(h2o_linklist_is_empty(&queue->receivers.inactive));
    pthread_mutex_destroy(&queue->mutex);

#if H2O_USE_LIBUV
    uv_close((uv_handle_t *)&queue->async, libuv_destroy_delayed);
#else
    h2o_socket_read_stop(queue->async.read);
    h2o_socket_close(queue->async.read);
#ifndef __linux__
    /* only one file descriptor is required for eventfd and already closed by h2o_socket_close() */
    close(queue->async.write);
#endif
    free(queue);
#endif
}