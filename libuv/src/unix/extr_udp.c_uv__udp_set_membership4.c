#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  fd; } ;
struct TYPE_11__ {TYPE_4__ io_watcher; } ;
typedef  TYPE_5__ uv_udp_t ;
typedef  int uv_membership ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq {TYPE_2__ imr_multiaddr; TYPE_1__ imr_interface; } ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int IP_ADD_MEMBERSHIP ; 
 int IP_DROP_MEMBERSHIP ; 
 int UV_EINVAL ; 
 int UV_ENODEV ; 
#define  UV_JOIN_GROUP 129 
#define  UV_LEAVE_GROUP 128 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ip_mreq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ip_mreq*,int) ; 
 int uv_inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__udp_set_membership4(uv_udp_t* handle,
                                   const struct sockaddr_in* multicast_addr,
                                   const char* interface_addr,
                                   uv_membership membership) {
  struct ip_mreq mreq;
  int optname;
  int err;

  memset(&mreq, 0, sizeof mreq);

  if (interface_addr) {
    err = uv_inet_pton(AF_INET, interface_addr, &mreq.imr_interface.s_addr);
    if (err)
      return err;
  } else {
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  }

  mreq.imr_multiaddr.s_addr = multicast_addr->sin_addr.s_addr;

  switch (membership) {
  case UV_JOIN_GROUP:
    optname = IP_ADD_MEMBERSHIP;
    break;
  case UV_LEAVE_GROUP:
    optname = IP_DROP_MEMBERSHIP;
    break;
  default:
    return UV_EINVAL;
  }

  if (setsockopt(handle->io_watcher.fd,
                 IPPROTO_IP,
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