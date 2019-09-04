#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * poll_cb; int /*<<< orphan*/  io_watcher; } ;
typedef  TYPE_1__ uv_poll_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int UV_EEXIST ; 
 int UV_ENOTTY ; 
 int /*<<< orphan*/  UV_POLL ; 
 scalar_t__ uv__fd_exists (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv__handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv__io_check_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv__io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int uv__nonblock (int,int) ; 
 int uv__nonblock_fcntl (int,int) ; 
 int uv__nonblock_ioctl (int,int) ; 
 int /*<<< orphan*/  uv__poll_io ; 

int uv_poll_init(uv_loop_t* loop, uv_poll_t* handle, int fd) {
  int err;

  if (uv__fd_exists(loop, fd))
    return UV_EEXIST;

  err = uv__io_check_fd(loop, fd);
  if (err)
    return err;

  /* If ioctl(FIONBIO) reports ENOTTY, try fcntl(F_GETFL) + fcntl(F_SETFL).
   * Workaround for e.g. kqueue fds not supporting ioctls.
   */
  err = uv__nonblock(fd, 1);
  if (err == UV_ENOTTY)
    if (uv__nonblock == uv__nonblock_ioctl)
      err = uv__nonblock_fcntl(fd, 1);

  if (err)
    return err;

  uv__handle_init(loop, (uv_handle_t*) handle, UV_POLL);
  uv__io_init(&handle->io_watcher, uv__poll_io, fd);
  handle->poll_cb = NULL;
  return 0;
}