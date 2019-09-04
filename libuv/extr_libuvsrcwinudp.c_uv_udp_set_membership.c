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
typedef  int /*<<< orphan*/  uv_membership ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int UV_EINVAL ; 
 int uv__udp_set_membership4 (int /*<<< orphan*/ *,struct sockaddr_in*,char const*,int /*<<< orphan*/ ) ; 
 int uv__udp_set_membership6 (int /*<<< orphan*/ *,struct sockaddr_in6*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_ip4_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 scalar_t__ uv_ip6_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_in6*) ; 

int uv_udp_set_membership(uv_udp_t* handle,
                          const char* multicast_addr,
                          const char* interface_addr,
                          uv_membership membership) {
  struct sockaddr_in addr4;
  struct sockaddr_in6 addr6;

  if (uv_ip4_addr(multicast_addr, 0, &addr4) == 0)
    return uv__udp_set_membership4(handle, &addr4, interface_addr, membership);
  else if (uv_ip6_addr(multicast_addr, 0, &addr6) == 0)
    return uv__udp_set_membership6(handle, &addr6, interface_addr, membership);
  else
    return UV_EINVAL;
}