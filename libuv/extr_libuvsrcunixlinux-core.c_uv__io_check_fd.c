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
struct TYPE_5__ {int /*<<< orphan*/  backend_fd; } ;
typedef  TYPE_2__ uv_loop_t ;
struct TYPE_4__ {int fd; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  POLLIN ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct epoll_event*,int /*<<< orphan*/ ,int) ; 

int uv__io_check_fd(uv_loop_t* loop, int fd) {
  struct epoll_event e;
  int rc;

  memset(&e, 0, sizeof(e));
  e.events = POLLIN;
  e.data.fd = -1;

  rc = 0;
  if (epoll_ctl(loop->backend_fd, EPOLL_CTL_ADD, fd, &e))
    if (errno != EEXIST)
      rc = UV__ERR(errno);

  if (rc == 0)
    if (epoll_ctl(loop->backend_fd, EPOLL_CTL_DEL, fd, &e))
      abort();

  return rc;
}