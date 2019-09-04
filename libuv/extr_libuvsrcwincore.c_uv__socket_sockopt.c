#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ uv_udp_t ;
struct TYPE_6__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_2__ uv_tcp_t ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_3__ uv_handle_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int UV_EINVAL ; 
 int UV_ENOTSUP ; 
 scalar_t__ UV_TCP ; 
 scalar_t__ UV_UDP ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int*) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv__socket_sockopt(uv_handle_t* handle, int optname, int* value) {
  int r;
  int len;
  SOCKET socket;

  if (handle == NULL || value == NULL)
    return UV_EINVAL;

  if (handle->type == UV_TCP)
    socket = ((uv_tcp_t*) handle)->socket;
  else if (handle->type == UV_UDP)
    socket = ((uv_udp_t*) handle)->socket;
  else
    return UV_ENOTSUP;

  len = sizeof(*value);

  if (*value == 0)
    r = getsockopt(socket, SOL_SOCKET, optname, (char*) value, &len);
  else
    r = setsockopt(socket, SOL_SOCKET, optname, (const char*) value, len);

  if (r == SOCKET_ERROR)
    return uv_translate_sys_error(WSAGetLastError());

  return 0;
}