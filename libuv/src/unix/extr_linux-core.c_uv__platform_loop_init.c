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
struct TYPE_3__ {int backend_fd; int inotify_fd; int /*<<< orphan*/ * inotify_watchers; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int UV__ERR (scalar_t__) ; 
 int epoll_create (int) ; 
 int epoll_create1 (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  uv__cloexec (int,int) ; 

int uv__platform_loop_init(uv_loop_t* loop) {
  int fd;

  /* It was reported that EPOLL_CLOEXEC is not defined on Android API < 21,
   * a.k.a. Lollipop. Since EPOLL_CLOEXEC is an alias for O_CLOEXEC on all
   * architectures, we just use that instead.
   */
#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
  fd = -1;
  errno = ENOSYS;
#else
  fd = epoll_create1(O_CLOEXEC);
#endif

  /* epoll_create1() can fail either because it's not implemented (old kernel)
   * or because it doesn't understand the O_CLOEXEC flag.
   */
  if (fd == -1 && (errno == ENOSYS || errno == EINVAL)) {
    fd = epoll_create(256);

    if (fd != -1)
      uv__cloexec(fd, 1);
  }

  loop->backend_fd = fd;
  loop->inotify_fd = -1;
  loop->inotify_watchers = NULL;

  if (fd == -1)
    return UV__ERR(errno);

  return 0;
}