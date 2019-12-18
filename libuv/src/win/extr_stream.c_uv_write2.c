#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_write_cb ;
struct TYPE_8__ {scalar_t__ type; int flags; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  ipc; } ;
typedef  TYPE_2__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int UV_EINVAL ; 
 int UV_EPIPE ; 
 int UV_HANDLE_WRITABLE ; 
 scalar_t__ UV_NAMED_PIPE ; 
 int uv__pipe_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  const*,unsigned int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int) ; 
 int uv_write (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

int uv_write2(uv_write_t* req,
              uv_stream_t* handle,
              const uv_buf_t bufs[],
              unsigned int nbufs,
              uv_stream_t* send_handle,
              uv_write_cb cb) {
  uv_loop_t* loop = handle->loop;
  int err;

  if (send_handle == NULL) {
    return uv_write(req, handle, bufs, nbufs, cb);
  }

  if (handle->type != UV_NAMED_PIPE || !((uv_pipe_t*) handle)->ipc) {
    return UV_EINVAL;
  } else if (!(handle->flags & UV_HANDLE_WRITABLE)) {
    return UV_EPIPE;
  }

  err = uv__pipe_write(
      loop, req, (uv_pipe_t*) handle, bufs, nbufs, send_handle, cb);
  return uv_translate_sys_error(err);
}