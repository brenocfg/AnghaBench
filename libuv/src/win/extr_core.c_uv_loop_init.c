#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ count; } ;
struct TYPE_10__ {int /*<<< orphan*/ * iocp; struct heap* timer_heap; int /*<<< orphan*/  wq_mutex; TYPE_6__ wq_async; scalar_t__ stop_flag; scalar_t__ timer_counter; scalar_t__ active_udp_streams; scalar_t__ active_tcp_streams; int /*<<< orphan*/  poll_peer_sockets; int /*<<< orphan*/ * next_idle_handle; int /*<<< orphan*/ * next_check_handle; int /*<<< orphan*/ * next_prepare_handle; int /*<<< orphan*/ * idle_handles; int /*<<< orphan*/ * prepare_handles; int /*<<< orphan*/ * check_handles; int /*<<< orphan*/ * endgame_handles; int /*<<< orphan*/ * pending_reqs_tail; scalar_t__ active_handles; TYPE_1__ active_reqs; int /*<<< orphan*/  handle_queue; int /*<<< orphan*/  wq; scalar_t__ time; } ;
typedef  TYPE_2__ uv_loop_t ;
struct heap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateIoCompletionPort (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  UV_HANDLE_INTERNAL ; 
 int /*<<< orphan*/  heap_init (struct heap*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__free (struct heap*) ; 
 int /*<<< orphan*/  uv__handle_unref (TYPE_6__*) ; 
 int uv__loops_add (TYPE_2__*) ; 
 struct heap* uv__malloc (int) ; 
 int /*<<< orphan*/  uv__once_init () ; 
 int /*<<< orphan*/  uv__work_done ; 
 int uv_async_init (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int uv_mutex_init (int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_update_time (TYPE_2__*) ; 

int uv_loop_init(uv_loop_t* loop) {
  struct heap* timer_heap;
  int err;

  /* Initialize libuv itself first */
  uv__once_init();

  /* Create an I/O completion port */
  loop->iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
  if (loop->iocp == NULL)
    return uv_translate_sys_error(GetLastError());

  /* To prevent uninitialized memory access, loop->time must be initialized
   * to zero before calling uv_update_time for the first time.
   */
  loop->time = 0;
  uv_update_time(loop);

  QUEUE_INIT(&loop->wq);
  QUEUE_INIT(&loop->handle_queue);
  loop->active_reqs.count = 0;
  loop->active_handles = 0;

  loop->pending_reqs_tail = NULL;

  loop->endgame_handles = NULL;

  loop->timer_heap = timer_heap = uv__malloc(sizeof(*timer_heap));
  if (timer_heap == NULL) {
    err = UV_ENOMEM;
    goto fail_timers_alloc;
  }

  heap_init(timer_heap);

  loop->check_handles = NULL;
  loop->prepare_handles = NULL;
  loop->idle_handles = NULL;

  loop->next_prepare_handle = NULL;
  loop->next_check_handle = NULL;
  loop->next_idle_handle = NULL;

  memset(&loop->poll_peer_sockets, 0, sizeof loop->poll_peer_sockets);

  loop->active_tcp_streams = 0;
  loop->active_udp_streams = 0;

  loop->timer_counter = 0;
  loop->stop_flag = 0;

  err = uv_mutex_init(&loop->wq_mutex);
  if (err)
    goto fail_mutex_init;

  err = uv_async_init(loop, &loop->wq_async, uv__work_done);
  if (err)
    goto fail_async_init;

  uv__handle_unref(&loop->wq_async);
  loop->wq_async.flags |= UV_HANDLE_INTERNAL;

  err = uv__loops_add(loop);
  if (err)
    goto fail_async_init;

  return 0;

fail_async_init:
  uv_mutex_destroy(&loop->wq_mutex);

fail_mutex_init:
  uv__free(timer_heap);
  loop->timer_heap = NULL;

fail_timers_alloc:
  CloseHandle(loop->iocp);
  loop->iocp = INVALID_HANDLE_VALUE;

  return err;
}