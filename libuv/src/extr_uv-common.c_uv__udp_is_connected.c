#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ uv_udp_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 scalar_t__ UV_UDP ; 
 scalar_t__ uv_udp_getpeername (TYPE_1__*,struct sockaddr*,int*) ; 

int uv__udp_is_connected(uv_udp_t* handle) {
  struct sockaddr_storage addr;
  int addrlen;
  if (handle->type != UV_UDP)
    return 0;

  addrlen = sizeof(addr);
  if (uv_udp_getpeername(handle, (struct sockaddr*) &addr, &addrlen) != 0)
    return 0;

  return addrlen > 0;
}