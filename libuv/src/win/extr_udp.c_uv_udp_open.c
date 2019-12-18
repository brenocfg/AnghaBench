#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_udp_t ;
typedef  int /*<<< orphan*/  uv_os_sock_t ;
struct TYPE_8__ {int /*<<< orphan*/  iAddressFamily; } ;
typedef  TYPE_2__ WSAPROTOCOL_INFOW ;

/* Variables and functions */
 int GetLastError () ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PROTOCOL_INFOW ; 
 int /*<<< orphan*/  UV_HANDLE_BOUND ; 
 int /*<<< orphan*/  UV_HANDLE_UDP_CONNECTED ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ uv__udp_is_bound (TYPE_1__*) ; 
 scalar_t__ uv__udp_is_connected (TYPE_1__*) ; 
 int uv_translate_sys_error (int) ; 
 int uv_udp_set_socket (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv_udp_open(uv_udp_t* handle, uv_os_sock_t sock) {
  WSAPROTOCOL_INFOW protocol_info;
  int opt_len;
  int err;

  /* Detect the address family of the socket. */
  opt_len = (int) sizeof protocol_info;
  if (getsockopt(sock,
                 SOL_SOCKET,
                 SO_PROTOCOL_INFOW,
                 (char*) &protocol_info,
                 &opt_len) == SOCKET_ERROR) {
    return uv_translate_sys_error(GetLastError());
  }

  err = uv_udp_set_socket(handle->loop,
                          handle,
                          sock,
                          protocol_info.iAddressFamily);
  if (err)
    return uv_translate_sys_error(err);

  if (uv__udp_is_bound(handle))
    handle->flags |= UV_HANDLE_BOUND;

  if (uv__udp_is_connected(handle))
    handle->flags |= UV_HANDLE_UDP_CONNECTED;

  return 0;
}