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
struct TYPE_3__ {int /*<<< orphan*/  backend_fd; } ;
typedef  TYPE_1__ uv_loop_t ;
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int uv__io_check_fd(uv_loop_t* loop, int fd) {
  struct kevent ev;
  int rc;

  rc = 0;
  EV_SET(&ev, fd, EVFILT_READ, EV_ADD, 0, 0, 0);
  if (kevent(loop->backend_fd, &ev, 1, NULL, 0, NULL))
    rc = UV__ERR(errno);

  EV_SET(&ev, fd, EVFILT_READ, EV_DELETE, 0, 0, 0);
  if (rc == 0)
    if (kevent(loop->backend_fd, &ev, 1, NULL, 0, NULL))
      abort();

  return rc;
}