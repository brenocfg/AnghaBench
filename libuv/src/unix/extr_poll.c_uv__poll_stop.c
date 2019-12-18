#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {TYPE_3__ io_watcher; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_poll_t ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int UV__POLLPRI ; 
 int UV__POLLRDHUP ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_stop (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  uv__platform_invalidate_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv__poll_stop(uv_poll_t* handle) {
  uv__io_stop(handle->loop,
              &handle->io_watcher,
              POLLIN | POLLOUT | UV__POLLRDHUP | UV__POLLPRI);
  uv__handle_stop(handle);
  uv__platform_invalidate_fd(handle->loop, handle->io_watcher.fd);
}