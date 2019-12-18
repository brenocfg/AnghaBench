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
struct TYPE_5__ {int fd; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct TYPE_6__ {int fd; int state; int epoll_state; scalar_t__ ready; } ;
typedef  TYPE_2__ event_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  EPOLL_CTL_MOD ; 
 int EVT_IN_EPOLL ; 
 int EVT_LEVEL ; 
 int EVT_NEW ; 
 int EVT_NOHUP ; 
 int EVT_RWX ; 
 TYPE_2__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int epoll_conv_flags (int) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  epoll_fd ; 
 int epoll_remove (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

int epoll_insert (int fd, int flags) {
  event_t *ev;
  int ef;
  struct epoll_event ee;
  if (!flags) {
    return epoll_remove (fd);
  }
  assert (fd >= 0 && fd < MAX_EVENTS);
  ev = Events + fd;
  if (ev->fd != fd) {
    memset (ev, 0, sizeof(event_t));
    ev->fd = fd;
  }
  flags &= EVT_NEW | EVT_NOHUP | EVT_LEVEL | EVT_RWX;
  ev->ready = 0; // !!! this bugfix led to some AIO-related bugs, now fixed with the aid of C_REPARSE flag
  if ((ev->state & (EVT_LEVEL | EVT_RWX | EVT_IN_EPOLL)) == flags + EVT_IN_EPOLL) {
    return 0;
  }
  ev->state = (ev->state & ~(EVT_LEVEL | EVT_RWX)) | (flags & (EVT_LEVEL | EVT_RWX));
  ef = epoll_conv_flags (flags);
  if (ef != ev->epoll_state || (flags & EVT_NEW) || !(ev->state & EVT_IN_EPOLL)) {
    ee.events = ef;
    ee.data.fd = fd; 

    vkprintf (1, "epoll_ctl(%d,%d,%d,%d,%08x)\n", epoll_fd, (ev->state & EVT_IN_EPOLL) ? EPOLL_CTL_MOD : EPOLL_CTL_ADD, fd, ee.data.fd, ee.events);

    if (epoll_ctl (epoll_fd, (ev->state & EVT_IN_EPOLL) ? EPOLL_CTL_MOD : EPOLL_CTL_ADD, fd, &ee) < 0) {
      perror("epoll_ctl()");
    }
    ev->state |= EVT_IN_EPOLL;
  }
  return 0;
}