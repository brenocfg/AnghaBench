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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_write_cb ;
typedef  int /*<<< orphan*/  uv_tty_t ;
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_3__ {int flags; int type; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int UV_EPIPE ; 
 int UV_HANDLE_WRITABLE ; 
#define  UV_NAMED_PIPE 130 
#define  UV_TCP 129 
#define  UV_TTY 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int uv__pipe_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_tcp_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int) ; 
 int uv_tty_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

int uv_write(uv_write_t* req,
             uv_stream_t* handle,
             const uv_buf_t bufs[],
             unsigned int nbufs,
             uv_write_cb cb) {
  uv_loop_t* loop = handle->loop;
  int err;

  if (!(handle->flags & UV_HANDLE_WRITABLE)) {
    return UV_EPIPE;
  }

  err = ERROR_INVALID_PARAMETER;
  switch (handle->type) {
    case UV_TCP:
      err = uv_tcp_write(loop, req, (uv_tcp_t*) handle, bufs, nbufs, cb);
      break;
    case UV_NAMED_PIPE:
      err = uv__pipe_write(
          loop, req, (uv_pipe_t*) handle, bufs, nbufs, NULL, cb);
      break;
    case UV_TTY:
      err = uv_tty_write(loop, req, (uv_tty_t*) handle, bufs, nbufs, cb);
      break;
    default:
      assert(0);
  }

  return uv_translate_sys_error(err);
}