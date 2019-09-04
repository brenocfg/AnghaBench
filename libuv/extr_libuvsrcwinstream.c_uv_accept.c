#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
#define  UV_NAMED_PIPE 129 
#define  UV_TCP 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int uv_pipe_accept (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int uv_tcp_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int) ; 

int uv_accept(uv_stream_t* server, uv_stream_t* client) {
  int err;

  err = ERROR_INVALID_PARAMETER;
  switch (server->type) {
    case UV_TCP:
      err = uv_tcp_accept((uv_tcp_t*)server, (uv_tcp_t*)client);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_accept((uv_pipe_t*)server, client);
      break;
    default:
      assert(0);
  }

  return uv_translate_sys_error(err);
}