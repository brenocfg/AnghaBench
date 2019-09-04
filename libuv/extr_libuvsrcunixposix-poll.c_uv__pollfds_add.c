#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t poll_fds_used; struct pollfd* poll_fds; int /*<<< orphan*/  poll_fds_iterating; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_7__ {scalar_t__ fd; int /*<<< orphan*/  pevents; } ;
typedef  TYPE_2__ uv__io_t ;
struct pollfd {scalar_t__ fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__pollfds_maybe_resize (TYPE_1__*) ; 

__attribute__((used)) static void uv__pollfds_add(uv_loop_t* loop, uv__io_t* w) {
  size_t i;
  struct pollfd* pe;

  /* If the fd is already in the set just update its events.  */
  assert(!loop->poll_fds_iterating);
  for (i = 0; i < loop->poll_fds_used; ++i) {
    if (loop->poll_fds[i].fd == w->fd) {
      loop->poll_fds[i].events = w->pevents;
      return;
    }
  }

  /* Otherwise, allocate a new slot in the set for the fd.  */
  uv__pollfds_maybe_resize(loop);
  pe = &loop->poll_fds[loop->poll_fds_used++];
  pe->fd = w->fd;
  pe->events = w->pevents;
}