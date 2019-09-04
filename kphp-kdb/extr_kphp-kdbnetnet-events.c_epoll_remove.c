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
struct TYPE_3__ {int fd; int state; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int EVT_IN_EPOLL ; 
 TYPE_1__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_fd ; 
 int /*<<< orphan*/  perror (char*) ; 

int epoll_remove (int fd) {
  event_t *ev;
  assert (fd >= 0 && fd < MAX_EVENTS);
  ev = Events + fd;
  if (ev->fd != fd) return -1;
  if (ev->state & EVT_IN_EPOLL) {
    ev->state &= ~EVT_IN_EPOLL;
    if (epoll_ctl (epoll_fd, EPOLL_CTL_DEL, fd, 0) < 0) {
      perror ("epoll_ctl()");
    }
  }
  return 0;
}