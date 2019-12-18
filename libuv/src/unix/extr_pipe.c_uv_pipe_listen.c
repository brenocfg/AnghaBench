#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cb; } ;
struct TYPE_5__ {TYPE_4__ io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  connection_cb; } ;
typedef  TYPE_1__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_connection_cb ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int SOMAXCONN ; 
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__server_io ; 
 int uv__stream_fd (TYPE_1__*) ; 

int uv_pipe_listen(uv_pipe_t* handle, int backlog, uv_connection_cb cb) {
  if (uv__stream_fd(handle) == -1)
    return UV_EINVAL;

#if defined(__MVS__)
  /* On zOS, backlog=0 has undefined behaviour */
  if (backlog == 0)
    backlog = 1;
  else if (backlog < 0)
    backlog = SOMAXCONN;
#endif

  if (listen(uv__stream_fd(handle), backlog))
    return UV__ERR(errno);

  handle->connection_cb = cb;
  handle->io_watcher.cb = uv__server_io;
  uv__io_start(handle->loop, &handle->io_watcher, POLLIN);
  return 0;
}