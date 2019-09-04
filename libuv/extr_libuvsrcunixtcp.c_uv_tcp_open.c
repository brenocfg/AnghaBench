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
struct TYPE_3__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_os_sock_t ;

/* Variables and functions */
 int UV_EEXIST ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 scalar_t__ uv__fd_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv__nonblock (int /*<<< orphan*/ ,int) ; 
 int uv__stream_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int uv_tcp_open(uv_tcp_t* handle, uv_os_sock_t sock) {
  int err;

  if (uv__fd_exists(handle->loop, sock))
    return UV_EEXIST;

  err = uv__nonblock(sock, 1);
  if (err)
    return err;

  return uv__stream_open((uv_stream_t*)handle,
                         sock,
                         UV_HANDLE_READABLE | UV_HANDLE_WRITABLE);
}