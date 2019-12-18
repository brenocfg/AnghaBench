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
struct TYPE_6__ {size_t poll_fds_used; TYPE_1__* poll_fds; int /*<<< orphan*/  poll_fds_iterating; } ;
typedef  TYPE_2__ uv_loop_t ;
struct TYPE_5__ {int fd; scalar_t__ revents; scalar_t__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__pollfds_swap (TYPE_2__*,size_t,size_t) ; 

__attribute__((used)) static void uv__pollfds_del(uv_loop_t* loop, int fd) {
  size_t i;
  assert(!loop->poll_fds_iterating);
  for (i = 0; i < loop->poll_fds_used;) {
    if (loop->poll_fds[i].fd == fd) {
      /* swap to last position and remove */
      --loop->poll_fds_used;
      uv__pollfds_swap(loop, i, loop->poll_fds_used);
      loop->poll_fds[loop->poll_fds_used].fd = -1;
      loop->poll_fds[loop->poll_fds_used].events = 0;
      loop->poll_fds[loop->poll_fds_used].revents = 0;
      /* This method is called with an fd of -1 to purge the invalidated fds,
       * so we may possibly have multiples to remove.
       */
      if (-1 != fd)
        return;
    } else {
      /* We must only increment the loop counter when the fds do not match.
       * Otherwise, when we are purging an invalidated fd, the value just
       * swapped here from the previous end of the array will be skipped.
       */
       ++i;
    }
  }
}