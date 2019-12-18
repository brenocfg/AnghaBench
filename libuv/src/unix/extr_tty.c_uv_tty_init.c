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
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  handle_queue; } ;
typedef  TYPE_1__ uv_tty_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  scalar_t__ uv_handle_type ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int UV_EINVAL ; 
 scalar_t__ UV_FILE ; 
 int UV_HANDLE_BLOCKING_WRITES ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 scalar_t__ UV_TTY ; 
 int /*<<< orphan*/  UV_TTY_MODE_NORMAL ; 
 scalar_t__ UV_UNKNOWN_HANDLE ; 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ttyname_r (int,char*,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__dup2_cloexec (int,int) ; 
 int /*<<< orphan*/  uv__nonblock (int,int) ; 
 int uv__open_cloexec (char*,int) ; 
 int /*<<< orphan*/  uv__stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  uv__stream_open (int /*<<< orphan*/ *,int,int) ; 
 int uv__stream_try_select (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ uv__tty_is_slave (int) ; 
 scalar_t__ uv_guess_handle (int) ; 

int uv_tty_init(uv_loop_t* loop, uv_tty_t* tty, int fd, int unused) {
  uv_handle_type type;
  int flags;
  int newfd;
  int r;
  int saved_flags;
  int mode;
  char path[256];
  (void)unused; /* deprecated parameter is no longer needed */

  /* File descriptors that refer to files cannot be monitored with epoll.
   * That restriction also applies to character devices like /dev/random
   * (but obviously not /dev/tty.)
   */
  type = uv_guess_handle(fd);
  if (type == UV_FILE || type == UV_UNKNOWN_HANDLE)
    return UV_EINVAL;

  flags = 0;
  newfd = -1;

  /* Save the fd flags in case we need to restore them due to an error. */
  do
    saved_flags = fcntl(fd, F_GETFL);
  while (saved_flags == -1 && errno == EINTR);

  if (saved_flags == -1)
    return UV__ERR(errno);
  mode = saved_flags & O_ACCMODE;

  /* Reopen the file descriptor when it refers to a tty. This lets us put the
   * tty in non-blocking mode without affecting other processes that share it
   * with us.
   *
   * Example: `node | cat` - if we put our fd 0 in non-blocking mode, it also
   * affects fd 1 of `cat` because both file descriptors refer to the same
   * struct file in the kernel. When we reopen our fd 0, it points to a
   * different struct file, hence changing its properties doesn't affect
   * other processes.
   */
  if (type == UV_TTY) {
    /* Reopening a pty in master mode won't work either because the reopened
     * pty will be in slave mode (*BSD) or reopening will allocate a new
     * master/slave pair (Linux). Therefore check if the fd points to a
     * slave device.
     */
    if (uv__tty_is_slave(fd) && ttyname_r(fd, path, sizeof(path)) == 0)
      r = uv__open_cloexec(path, mode);
    else
      r = -1;

    if (r < 0) {
      /* fallback to using blocking writes */
      if (mode != O_RDONLY)
        flags |= UV_HANDLE_BLOCKING_WRITES;
      goto skip;
    }

    newfd = r;

    r = uv__dup2_cloexec(newfd, fd);
    if (r < 0 && r != UV_EINVAL) {
      /* EINVAL means newfd == fd which could conceivably happen if another
       * thread called close(fd) between our calls to isatty() and open().
       * That's a rather unlikely event but let's handle it anyway.
       */
      uv__close(newfd);
      return r;
    }

    fd = newfd;
  }

skip:
  uv__stream_init(loop, (uv_stream_t*) tty, UV_TTY);

  /* If anything fails beyond this point we need to remove the handle from
   * the handle queue, since it was added by uv__handle_init in uv_stream_init.
   */

  if (!(flags & UV_HANDLE_BLOCKING_WRITES))
    uv__nonblock(fd, 1);

#if defined(__APPLE__)
  r = uv__stream_try_select((uv_stream_t*) tty, &fd);
  if (r) {
    int rc = r;
    if (newfd != -1)
      uv__close(newfd);
    QUEUE_REMOVE(&tty->handle_queue);
    do
      r = fcntl(fd, F_SETFL, saved_flags);
    while (r == -1 && errno == EINTR);
    return rc;
  }
#endif

  if (mode != O_WRONLY)
    flags |= UV_HANDLE_READABLE;
  if (mode != O_RDONLY)
    flags |= UV_HANDLE_WRITABLE;

  uv__stream_open((uv_stream_t*) tty, fd, flags);
  tty->mode = UV_TTY_MODE_NORMAL;

  return 0;
}