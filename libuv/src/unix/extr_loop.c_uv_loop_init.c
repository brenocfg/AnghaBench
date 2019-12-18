#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {int fd; } ;
struct TYPE_15__ {scalar_t__ count; } ;
struct TYPE_17__ {int async_wfd; int* signal_pipefd; int backend_fd; int emfile_fd; int /*<<< orphan*/  cloexec_lock; int /*<<< orphan*/  wq_mutex; TYPE_5__ wq_async; int /*<<< orphan*/  process_handles; TYPE_5__ child_watcher; scalar_t__ stop_flag; scalar_t__ timer_counter; TYPE_2__ async_io_watcher; int /*<<< orphan*/ * closing_handles; int /*<<< orphan*/  watcher_queue; int /*<<< orphan*/  pending_queue; scalar_t__ nwatchers; int /*<<< orphan*/ * watchers; scalar_t__ nfds; TYPE_1__ active_reqs; scalar_t__ active_handles; int /*<<< orphan*/  handle_queue; int /*<<< orphan*/  prepare_handles; int /*<<< orphan*/  check_handles; int /*<<< orphan*/  async_handles; int /*<<< orphan*/  idle_handles; int /*<<< orphan*/  wq; int /*<<< orphan*/  timer_heap; void* data; } ;
typedef  TYPE_3__ uv_loop_t ;
struct heap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UV_HANDLE_INTERNAL ; 
 int /*<<< orphan*/  heap_init (struct heap*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__handle_unref (TYPE_5__*) ; 
 int /*<<< orphan*/  uv__platform_loop_delete (TYPE_3__*) ; 
 int uv__platform_loop_init (TYPE_3__*) ; 
 int /*<<< orphan*/  uv__signal_global_once_init () ; 
 int /*<<< orphan*/  uv__signal_loop_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  uv__update_time (TYPE_3__*) ; 
 int /*<<< orphan*/  uv__work_done ; 
 int uv_async_init (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int uv_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_destroy (int /*<<< orphan*/ *) ; 
 int uv_rwlock_init (int /*<<< orphan*/ *) ; 
 int uv_signal_init (TYPE_3__*,TYPE_5__*) ; 

int uv_loop_init(uv_loop_t* loop) {
  void* saved_data;
  int err;


  saved_data = loop->data;
  memset(loop, 0, sizeof(*loop));
  loop->data = saved_data;

  heap_init((struct heap*) &loop->timer_heap);
  QUEUE_INIT(&loop->wq);
  QUEUE_INIT(&loop->idle_handles);
  QUEUE_INIT(&loop->async_handles);
  QUEUE_INIT(&loop->check_handles);
  QUEUE_INIT(&loop->prepare_handles);
  QUEUE_INIT(&loop->handle_queue);

  loop->active_handles = 0;
  loop->active_reqs.count = 0;
  loop->nfds = 0;
  loop->watchers = NULL;
  loop->nwatchers = 0;
  QUEUE_INIT(&loop->pending_queue);
  QUEUE_INIT(&loop->watcher_queue);

  loop->closing_handles = NULL;
  uv__update_time(loop);
  loop->async_io_watcher.fd = -1;
  loop->async_wfd = -1;
  loop->signal_pipefd[0] = -1;
  loop->signal_pipefd[1] = -1;
  loop->backend_fd = -1;
  loop->emfile_fd = -1;

  loop->timer_counter = 0;
  loop->stop_flag = 0;

  err = uv__platform_loop_init(loop);
  if (err)
    return err;

  uv__signal_global_once_init();
  err = uv_signal_init(loop, &loop->child_watcher);
  if (err)
    goto fail_signal_init;

  uv__handle_unref(&loop->child_watcher);
  loop->child_watcher.flags |= UV_HANDLE_INTERNAL;
  QUEUE_INIT(&loop->process_handles);

  err = uv_rwlock_init(&loop->cloexec_lock);
  if (err)
    goto fail_rwlock_init;

  err = uv_mutex_init(&loop->wq_mutex);
  if (err)
    goto fail_mutex_init;

  err = uv_async_init(loop, &loop->wq_async, uv__work_done);
  if (err)
    goto fail_async_init;

  uv__handle_unref(&loop->wq_async);
  loop->wq_async.flags |= UV_HANDLE_INTERNAL;

  return 0;

fail_async_init:
  uv_mutex_destroy(&loop->wq_mutex);

fail_mutex_init:
  uv_rwlock_destroy(&loop->cloexec_lock);

fail_rwlock_init:
  uv__signal_loop_cleanup(loop);

fail_signal_init:
  uv__platform_loop_delete(loop);

  return err;
}