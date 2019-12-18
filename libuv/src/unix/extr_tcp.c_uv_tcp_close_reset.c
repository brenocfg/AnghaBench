#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_close_cb ;
struct linger {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  l ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int UV_EINVAL ; 
 int UV_HANDLE_SHUTTING ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct linger*,int) ; 
 int uv__stream_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_tcp_close_reset(uv_tcp_t* handle, uv_close_cb close_cb) {
  int fd;
  struct linger l = { 1, 0 };

  /* Disallow setting SO_LINGER to zero due to some platform inconsistencies */
  if (handle->flags & UV_HANDLE_SHUTTING)
    return UV_EINVAL;

  fd = uv__stream_fd(handle);
  if (0 != setsockopt(fd, SOL_SOCKET, SO_LINGER, &l, sizeof(l)))
    return UV__ERR(errno);

  uv_close((uv_handle_t*) handle, close_cb);
  return 0;
}