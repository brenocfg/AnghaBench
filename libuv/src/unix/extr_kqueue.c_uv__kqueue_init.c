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
struct TYPE_3__ {int backend_fd; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int kqueue () ; 
 int /*<<< orphan*/  uv__cloexec (int,int) ; 

int uv__kqueue_init(uv_loop_t* loop) {
  loop->backend_fd = kqueue();
  if (loop->backend_fd == -1)
    return UV__ERR(errno);

  uv__cloexec(loop->backend_fd, 1);

  return 0;
}