#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * close_cb; int /*<<< orphan*/  async_sent; } ;
struct TYPE_7__ {scalar_t__* poll_peer_sockets; int /*<<< orphan*/  iocp; int /*<<< orphan*/ * timer_heap; int /*<<< orphan*/  wq_mutex; int /*<<< orphan*/  wq; TYPE_5__ wq_async; } ;
typedef  TYPE_1__ uv_loop_t ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__handle_close (TYPE_5__*) ; 
 int /*<<< orphan*/  uv__handle_closing (TYPE_5__*) ; 
 int /*<<< orphan*/  uv__has_active_reqs (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__loops_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

void uv__loop_close(uv_loop_t* loop) {
  size_t i;

  uv__loops_remove(loop);

  /* close the async handle without needing an extra loop iteration */
  assert(!loop->wq_async.async_sent);
  loop->wq_async.close_cb = NULL;
  uv__handle_closing(&loop->wq_async);
  uv__handle_close(&loop->wq_async);

  for (i = 0; i < ARRAY_SIZE(loop->poll_peer_sockets); i++) {
    SOCKET sock = loop->poll_peer_sockets[i];
    if (sock != 0 && sock != INVALID_SOCKET)
      closesocket(sock);
  }

  uv_mutex_lock(&loop->wq_mutex);
  assert(QUEUE_EMPTY(&loop->wq) && "thread pool work queue not empty!");
  assert(!uv__has_active_reqs(loop));
  uv_mutex_unlock(&loop->wq_mutex);
  uv_mutex_destroy(&loop->wq_mutex);

  uv__free(loop->timer_heap);
  loop->timer_heap = NULL;

  CloseHandle(loop->iocp);
}