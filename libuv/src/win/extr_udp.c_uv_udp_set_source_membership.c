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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int uv__udp_set_source_membership4 (int /*<<< orphan*/ *,struct sockaddr_in*,char const*,struct sockaddr_in*,int /*<<< orphan*/ ) ; 
 int uv__udp_set_source_membership6 (int /*<<< orphan*/ *,struct sockaddr_in6*,char const*,struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int uv_ip4_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_ip6_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_in6*) ; 

int uv_udp_set_source_membership(uv_udp_t* handle,
                                 const char* multicast_addr,
                                 const char* interface_addr,
                                 const char* source_addr,
                                 uv_membership membership) {
  int err;
  struct sockaddr_storage mcast_addr;
  struct sockaddr_in* mcast_addr4;
  struct sockaddr_in6* mcast_addr6;
  struct sockaddr_storage src_addr;
  struct sockaddr_in* src_addr4;
  struct sockaddr_in6* src_addr6;

  mcast_addr4 = (struct sockaddr_in*)&mcast_addr;
  mcast_addr6 = (struct sockaddr_in6*)&mcast_addr;
  src_addr4 = (struct sockaddr_in*)&src_addr;
  src_addr6 = (struct sockaddr_in6*)&src_addr;

  err = uv_ip4_addr(multicast_addr, 0, mcast_addr4);
  if (err) {
    err = uv_ip6_addr(multicast_addr, 0, mcast_addr6);
    if (err)
      return err;
    err = uv_ip6_addr(source_addr, 0, src_addr6);
    if (err)
      return err;
    return uv__udp_set_source_membership6(handle,
                                          mcast_addr6,
                                          interface_addr,
                                          src_addr6,
                                          membership);
  }
  
  err = uv_ip4_addr(source_addr, 0, src_addr4);
  if (err)
    return err;
  return uv__udp_set_source_membership4(handle,
                                        mcast_addr4,
                                        interface_addr,
                                        src_addr4,
                                        membership);
}