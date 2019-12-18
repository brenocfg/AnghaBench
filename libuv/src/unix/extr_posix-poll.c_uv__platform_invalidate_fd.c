#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t poll_fds_used; TYPE_1__* poll_fds; scalar_t__ poll_fds_iterating; } ;
typedef  TYPE_2__ uv_loop_t ;
struct TYPE_5__ {int fd; scalar_t__ revents; scalar_t__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__pollfds_del (TYPE_2__*,int) ; 

void uv__platform_invalidate_fd(uv_loop_t* loop, int fd) {
  size_t i;

  assert(fd >= 0);

  if (loop->poll_fds_iterating) {
    /* uv__io_poll is currently iterating.  Just invalidate fd.  */
    for (i = 0; i < loop->poll_fds_used; i++)
      if (loop->poll_fds[i].fd == fd) {
        loop->poll_fds[i].fd = -1;
        loop->poll_fds[i].events = 0;
        loop->poll_fds[i].revents = 0;
      }
  } else {
    /* uv__io_poll is not iterating.  Delete fd from the set.  */
    uv__pollfds_del(loop, fd);
  }
}