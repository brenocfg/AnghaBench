#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
struct epoll_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  embed_async ; 
 int /*<<< orphan*/  embed_closed ; 
 int /*<<< orphan*/  embed_sem ; 
 int epoll_wait (int,struct epoll_event*,int,int) ; 
 scalar_t__ errno ; 
 int kevent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  uv_async_send (int /*<<< orphan*/ *) ; 
 int uv_backend_fd (int /*<<< orphan*/ ) ; 
 int uv_backend_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void embed_thread_runner(void* arg) {
  int r;
  int fd;
  int timeout;

  while (!embed_closed) {
    fd = uv_backend_fd(uv_default_loop());
    timeout = uv_backend_timeout(uv_default_loop());

    do {
#if defined(HAVE_KQUEUE)
      struct timespec ts;
      ts.tv_sec = timeout / 1000;
      ts.tv_nsec = (timeout % 1000) * 1000000;
      r = kevent(fd, NULL, 0, NULL, 0, &ts);
#elif defined(HAVE_EPOLL)
      {
        struct epoll_event ev;
        r = epoll_wait(fd, &ev, 1, timeout);
      }
#endif
    } while (r == -1 && errno == EINTR);
    uv_async_send(&embed_async);
    uv_sem_wait(&embed_sem);
  }
}