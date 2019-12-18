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
struct TYPE_3__ {size_t nwatchers; scalar_t__ backend_fd; scalar_t__* watchers; } ;
typedef  TYPE_1__ uv_loop_t ;
struct pollfd {int fd; } ;
struct poll_ctl {int fd; int /*<<< orphan*/  cmd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pollset_ctl (scalar_t__,struct poll_ctl*,int) ; 

void uv__platform_invalidate_fd(uv_loop_t* loop, int fd) {
  struct pollfd* events;
  uintptr_t i;
  uintptr_t nfds;
  struct poll_ctl pc;

  assert(loop->watchers != NULL);
  assert(fd >= 0);

  events = (struct pollfd*) loop->watchers[loop->nwatchers];
  nfds = (uintptr_t) loop->watchers[loop->nwatchers + 1];

  if (events != NULL)
    /* Invalidate events with same file descriptor */
    for (i = 0; i < nfds; i++)
      if ((int) events[i].fd == fd)
        events[i].fd = -1;

  /* Remove the file descriptor from the poll set */
  pc.events = 0;
  pc.cmd = PS_DELETE;
  pc.fd = fd;
  if(loop->backend_fd >= 0)
    pollset_ctl(loop->backend_fd, &pc, 1);
}