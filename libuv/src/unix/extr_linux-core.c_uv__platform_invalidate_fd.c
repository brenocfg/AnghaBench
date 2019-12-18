#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t nwatchers; scalar_t__ backend_fd; scalar_t__* watchers; } ;
typedef  TYPE_2__ uv_loop_t ;
struct TYPE_4__ {int fd; } ;
struct epoll_event {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  epoll_ctl (scalar_t__,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  memset (struct epoll_event*,int /*<<< orphan*/ ,int) ; 

void uv__platform_invalidate_fd(uv_loop_t* loop, int fd) {
  struct epoll_event* events;
  struct epoll_event dummy;
  uintptr_t i;
  uintptr_t nfds;

  assert(loop->watchers != NULL);
  assert(fd >= 0);

  events = (struct epoll_event*) loop->watchers[loop->nwatchers];
  nfds = (uintptr_t) loop->watchers[loop->nwatchers + 1];
  if (events != NULL)
    /* Invalidate events with same file descriptor */
    for (i = 0; i < nfds; i++)
      if (events[i].data.fd == fd)
        events[i].data.fd = -1;

  /* Remove the file descriptor from the epoll.
   * This avoids a problem where the same file description remains open
   * in another process, causing repeated junk epoll events.
   *
   * We pass in a dummy epoll_event, to work around a bug in old kernels.
   */
  if (loop->backend_fd >= 0) {
    /* Work around a bug in kernels 3.10 to 3.19 where passing a struct that
     * has the EPOLLWAKEUP flag set generates spurious audit syslog warnings.
     */
    memset(&dummy, 0, sizeof(dummy));
    epoll_ctl(loop->backend_fd, EPOLL_CTL_DEL, fd, &dummy);
  }
}