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
struct TYPE_3__ {scalar_t__ socket; } ;
typedef  TYPE_1__ uv_udp_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int UV_EBADF ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_udp_set_broadcast(uv_udp_t* handle, int value) {
  BOOL optval = (BOOL) value;

  if (handle->socket == INVALID_SOCKET)
    return UV_EBADF;

  if (setsockopt(handle->socket,
                 SOL_SOCKET,
                 SO_BROADCAST,
                 (char*) &optval,
                 sizeof optval)) {
    return uv_translate_sys_error(WSAGetLastError());
  }

  return 0;
}