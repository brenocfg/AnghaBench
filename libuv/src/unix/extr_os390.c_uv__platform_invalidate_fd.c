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
struct TYPE_3__ {size_t nwatchers; int /*<<< orphan*/ * ep; scalar_t__* watchers; } ;
typedef  TYPE_1__ uv_loop_t ;
struct epoll_event {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  epoll_ctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct epoll_event*) ; 

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
      if ((int) events[i].fd == fd)
        events[i].fd = -1;

  /* Remove the file descriptor from the epoll. */
  if (loop->ep != NULL)
    epoll_ctl(loop->ep, EPOLL_CTL_DEL, fd, &dummy);
}