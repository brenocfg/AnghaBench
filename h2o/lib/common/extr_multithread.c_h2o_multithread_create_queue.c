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
typedef  int /*<<< orphan*/  uv_async_cb ;
struct TYPE_7__ {int /*<<< orphan*/  inactive; int /*<<< orphan*/  active; } ;
struct TYPE_8__ {TYPE_1__ receivers; int /*<<< orphan*/  mutex; int /*<<< orphan*/  async; } ;
typedef  TYPE_2__ h2o_multithread_queue_t ;
typedef  int /*<<< orphan*/  h2o_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_linklist_init_anchor (int /*<<< orphan*/ *) ; 
 TYPE_2__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  init_async (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ queue_cb ; 
 int /*<<< orphan*/  uv_async_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

h2o_multithread_queue_t *h2o_multithread_create_queue(h2o_loop_t *loop)
{
    h2o_multithread_queue_t *queue = h2o_mem_alloc(sizeof(*queue));
    memset(queue, 0, sizeof(*queue));

#if H2O_USE_LIBUV
    uv_async_init(loop, &queue->async, (uv_async_cb)queue_cb);
#else
    init_async(queue, loop);
#endif
    pthread_mutex_init(&queue->mutex, NULL);
    h2o_linklist_init_anchor(&queue->receivers.active);
    h2o_linklist_init_anchor(&queue->receivers.inactive);

    return queue;
}