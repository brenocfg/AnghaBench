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
struct poll_ctl {int fd; int /*<<< orphan*/  cmd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  PS_DELETE ; 
 int /*<<< orphan*/  PS_MOD ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ pollset_ctl (int /*<<< orphan*/ ,struct poll_ctl*,int) ; 

int uv__io_check_fd(uv_loop_t* loop, int fd) {
  struct poll_ctl pc;

  pc.events = POLLIN;
  pc.cmd = PS_MOD;  /* Equivalent to PS_ADD if the fd is not in the pollset. */
  pc.fd = fd;

  if (pollset_ctl(loop->backend_fd, &pc, 1))
    return UV__ERR(errno);

  pc.cmd = PS_DELETE;
  if (pollset_ctl(loop->backend_fd, &pc, 1))
    abort();

  return 0;
}