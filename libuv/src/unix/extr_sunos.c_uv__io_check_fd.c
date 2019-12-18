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

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  PORT_SOURCE_FD ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ port_associate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ port_dissociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int uv__io_check_fd(uv_loop_t* loop, int fd) {
  if (port_associate(loop->backend_fd, PORT_SOURCE_FD, fd, POLLIN, 0))
    return UV__ERR(errno);

  if (port_dissociate(loop->backend_fd, PORT_SOURCE_FD, fd)) {
    perror("(libuv) port_dissociate()");
    abort();
  }

  return 0;
}