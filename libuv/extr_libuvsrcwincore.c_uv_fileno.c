#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ uv_udp_t ;
struct TYPE_10__ {scalar_t__ handle; } ;
typedef  TYPE_2__ uv_tty_t ;
struct TYPE_11__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_3__ uv_tcp_t ;
struct TYPE_12__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_4__ uv_poll_t ;
struct TYPE_13__ {scalar_t__ handle; } ;
typedef  TYPE_5__ uv_pipe_t ;
typedef  scalar_t__ uv_os_fd_t ;
struct TYPE_14__ {int type; } ;
typedef  TYPE_6__ uv_handle_t ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int UV_EBADF ; 
 int UV_EINVAL ; 
#define  UV_NAMED_PIPE 132 
#define  UV_POLL 131 
#define  UV_TCP 130 
#define  UV_TTY 129 
#define  UV_UDP 128 
 scalar_t__ uv_is_closing (TYPE_6__ const*) ; 

int uv_fileno(const uv_handle_t* handle, uv_os_fd_t* fd) {
  uv_os_fd_t fd_out;

  switch (handle->type) {
  case UV_TCP:
    fd_out = (uv_os_fd_t)((uv_tcp_t*) handle)->socket;
    break;

  case UV_NAMED_PIPE:
    fd_out = ((uv_pipe_t*) handle)->handle;
    break;

  case UV_TTY:
    fd_out = ((uv_tty_t*) handle)->handle;
    break;

  case UV_UDP:
    fd_out = (uv_os_fd_t)((uv_udp_t*) handle)->socket;
    break;

  case UV_POLL:
    fd_out = (uv_os_fd_t)((uv_poll_t*) handle)->socket;
    break;

  default:
    return UV_EINVAL;
  }

  if (uv_is_closing(handle) || fd_out == INVALID_HANDLE_VALUE)
    return UV_EBADF;

  *fd = fd_out;
  return 0;
}