#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_udp_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 scalar_t__ uv_udp_getsockname (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 

int uv__udp_is_bound(uv_udp_t* handle) {
  struct sockaddr_storage addr;
  int addrlen;

  addrlen = sizeof(addr);
  if (uv_udp_getsockname(handle, (struct sockaddr*) &addr, &addrlen) != 0)
    return 0;

  return addrlen > 0;
}