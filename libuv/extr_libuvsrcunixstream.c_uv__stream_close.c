#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int fd; } ;
struct TYPE_9__ {int flags; int accepted_fd; TYPE_5__ io_watcher; TYPE_2__* queued_fds; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_10__ {unsigned int offset; int* fds; } ;
typedef  TYPE_2__ uv__stream_queued_fds_t ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int STDERR_FILENO ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (TYPE_2__*) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_active (TYPE_5__*,int) ; 
 int /*<<< orphan*/  uv__io_close (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  uv_read_stop (TYPE_1__*) ; 

void uv__stream_close(uv_stream_t* handle) {
  unsigned int i;
  uv__stream_queued_fds_t* queued_fds;

#if defined(__APPLE__)
  /* Terminate select loop first */
  if (handle->select != NULL) {
    uv__stream_select_t* s;

    s = handle->select;

    uv_sem_post(&s->close_sem);
    uv_sem_post(&s->async_sem);
    uv__stream_osx_interrupt_select(handle);
    uv_thread_join(&s->thread);
    uv_sem_destroy(&s->close_sem);
    uv_sem_destroy(&s->async_sem);
    uv__close(s->fake_fd);
    uv__close(s->int_fd);
    uv_close((uv_handle_t*) &s->async, uv__stream_osx_cb_close);

    handle->select = NULL;
  }
#endif /* defined(__APPLE__) */

  uv__io_close(handle->loop, &handle->io_watcher);
  uv_read_stop(handle);
  uv__handle_stop(handle);
  handle->flags &= ~(UV_HANDLE_READABLE | UV_HANDLE_WRITABLE);

  if (handle->io_watcher.fd != -1) {
    /* Don't close stdio file descriptors.  Nothing good comes from it. */
    if (handle->io_watcher.fd > STDERR_FILENO)
      uv__close(handle->io_watcher.fd);
    handle->io_watcher.fd = -1;
  }

  if (handle->accepted_fd != -1) {
    uv__close(handle->accepted_fd);
    handle->accepted_fd = -1;
  }

  /* Close all queued fds */
  if (handle->queued_fds != NULL) {
    queued_fds = handle->queued_fds;
    for (i = 0; i < queued_fds->offset; i++)
      uv__close(queued_fds->fds[i]);
    uv__free(handle->queued_fds);
    handle->queued_fds = NULL;
  }

  assert(!uv__io_active(&handle->io_watcher, POLLIN | POLLOUT));
}