#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fd; } ;
struct TYPE_10__ {TYPE_1__ io_watcher; } ;
typedef  TYPE_3__ uv_udp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_9__ {int fd; } ;
struct TYPE_11__ {TYPE_2__ io_watcher; } ;
typedef  TYPE_4__ uv_poll_t ;
typedef  int uv_os_fd_t ;
struct TYPE_12__ {int type; } ;
typedef  TYPE_5__ uv_handle_t ;

/* Variables and functions */
 int UV_EBADF ; 
 int UV_EINVAL ; 
#define  UV_NAMED_PIPE 132 
#define  UV_POLL 131 
#define  UV_TCP 130 
#define  UV_TTY 129 
#define  UV_UDP 128 
 scalar_t__ uv__is_closing (TYPE_5__ const*) ; 
 int uv__stream_fd (int /*<<< orphan*/ *) ; 

int uv_fileno(const uv_handle_t* handle, uv_os_fd_t* fd) {
  int fd_out;

  switch (handle->type) {
  case UV_TCP:
  case UV_NAMED_PIPE:
  case UV_TTY:
    fd_out = uv__stream_fd((uv_stream_t*) handle);
    break;

  case UV_UDP:
    fd_out = ((uv_udp_t *) handle)->io_watcher.fd;
    break;

  case UV_POLL:
    fd_out = ((uv_poll_t *) handle)->io_watcher.fd;
    break;

  default:
    return UV_EINVAL;
  }

  if (uv__is_closing(handle) || fd_out == -1)
    return UV_EBADF;

  *fd = fd_out;
  return 0;
}