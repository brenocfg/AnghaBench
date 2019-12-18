#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {TYPE_1__ io_watcher; } ;
typedef  TYPE_2__ uv_udp_t ;
typedef  int uv_membership ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_scope_id; } ;
struct ipv6_mreq {int /*<<< orphan*/  ipv6mr_multiaddr; scalar_t__ ipv6mr_interface; } ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int IPV6_ADD_MEMBERSHIP ; 
 int IPV6_DROP_MEMBERSHIP ; 
 int UV_EINVAL ; 
 int UV_ENODEV ; 
#define  UV_JOIN_GROUP 129 
#define  UV_LEAVE_GROUP 128 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct ipv6_mreq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ipv6_mreq*,int) ; 
 scalar_t__ uv_ip6_addr (char const*,int /*<<< orphan*/ ,struct sockaddr_in6*) ; 

__attribute__((used)) static int uv__udp_set_membership6(uv_udp_t* handle,
                                   const struct sockaddr_in6* multicast_addr,
                                   const char* interface_addr,
                                   uv_membership membership) {
  int optname;
  struct ipv6_mreq mreq;
  struct sockaddr_in6 addr6;

  memset(&mreq, 0, sizeof mreq);

  if (interface_addr) {
    if (uv_ip6_addr(interface_addr, 0, &addr6))
      return UV_EINVAL;
    mreq.ipv6mr_interface = addr6.sin6_scope_id;
  } else {
    mreq.ipv6mr_interface = 0;
  }

  mreq.ipv6mr_multiaddr = multicast_addr->sin6_addr;

  switch (membership) {
  case UV_JOIN_GROUP:
    optname = IPV6_ADD_MEMBERSHIP;
    break;
  case UV_LEAVE_GROUP:
    optname = IPV6_DROP_MEMBERSHIP;
    break;
  default:
    return UV_EINVAL;
  }

  if (setsockopt(handle->io_watcher.fd,
                 IPPROTO_IPV6,
                 optname,
                 &mreq,
                 sizeof(mreq))) {
#if defined(__MVS__)
  if (errno == ENXIO)
    return UV_ENODEV;
#endif
    return UV__ERR(errno);
  }

  return 0;
}