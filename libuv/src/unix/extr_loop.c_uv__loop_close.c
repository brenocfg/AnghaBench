#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int emfile_fd; int backend_fd; scalar_t__ nfds; scalar_t__ nwatchers; int /*<<< orphan*/ * watchers; int /*<<< orphan*/  watcher_queue; int /*<<< orphan*/  pending_queue; int /*<<< orphan*/  cloexec_lock; int /*<<< orphan*/  wq_mutex; int /*<<< orphan*/  wq; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__async_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__has_active_reqs (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__platform_loop_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__signal_loop_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_destroy (int /*<<< orphan*/ *) ; 

void uv__loop_close(uv_loop_t* loop) {
  uv__signal_loop_cleanup(loop);
  uv__platform_loop_delete(loop);
  uv__async_stop(loop);

  if (loop->emfile_fd != -1) {
    uv__close(loop->emfile_fd);
    loop->emfile_fd = -1;
  }

  if (loop->backend_fd != -1) {
    uv__close(loop->backend_fd);
    loop->backend_fd = -1;
  }

  uv_mutex_lock(&loop->wq_mutex);
  assert(QUEUE_EMPTY(&loop->wq) && "thread pool work queue not empty!");
  assert(!uv__has_active_reqs(loop));
  uv_mutex_unlock(&loop->wq_mutex);
  uv_mutex_destroy(&loop->wq_mutex);

  /*
   * Note that all thread pool stuff is finished at this point and
   * it is safe to just destroy rw lock
   */
  uv_rwlock_destroy(&loop->cloexec_lock);

#if 0
  assert(QUEUE_EMPTY(&loop->pending_queue));
  assert(QUEUE_EMPTY(&loop->watcher_queue));
  assert(loop->nfds == 0);
#endif

  uv__free(loop->watchers);
  loop->watchers = NULL;
  loop->nwatchers = 0;
}