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
typedef  int /*<<< orphan*/  uv_tty_t ;
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_3__ {int flags; int type; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_read_cb ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_alloc_cb ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int UV_EALREADY ; 
 int UV_ENOTCONN ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_READING ; 
#define  UV_NAMED_PIPE 130 
#define  UV_TCP 129 
#define  UV_TTY 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int uv_pipe_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int) ; 
 int uv_tty_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv_read_start(uv_stream_t* handle, uv_alloc_cb alloc_cb,
    uv_read_cb read_cb) {
  int err;

  if (handle->flags & UV_HANDLE_READING) {
    return UV_EALREADY;
  }

  if (!(handle->flags & UV_HANDLE_READABLE)) {
    return UV_ENOTCONN;
  }

  err = ERROR_INVALID_PARAMETER;
  switch (handle->type) {
    case UV_TCP:
      err = uv_tcp_read_start((uv_tcp_t*)handle, alloc_cb, read_cb);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_read_start((uv_pipe_t*)handle, alloc_cb, read_cb);
      break;
    case UV_TTY:
      err = uv_tty_read_start((uv_tty_t*) handle, alloc_cb, read_cb);
      break;
    default:
      assert(0);
  }

  return uv_translate_sys_error(err);
}