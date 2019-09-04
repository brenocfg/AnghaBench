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
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_connection_cb ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
#define  UV_NAMED_PIPE 129 
#define  UV_TCP 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int uv_pipe_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int uv_tcp_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int) ; 

int uv_listen(uv_stream_t* stream, int backlog, uv_connection_cb cb) {
  int err;

  err = ERROR_INVALID_PARAMETER;
  switch (stream->type) {
    case UV_TCP:
      err = uv_tcp_listen((uv_tcp_t*)stream, backlog, cb);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_listen((uv_pipe_t*)stream, backlog, cb);
      break;
    default:
      assert(0);
  }

  return uv_translate_sys_error(err);
}