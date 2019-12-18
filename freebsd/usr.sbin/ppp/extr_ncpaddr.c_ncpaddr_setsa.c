#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct ncpaddr {int ncpaddr_family; TYPE_2__ ncpaddr_ip6addr; TYPE_1__ ncpaddr_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int AF_UNSPEC ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (TYPE_2__*) ; 

void
ncpaddr_setsa(struct ncpaddr *addr, const struct sockaddr *host)
{
  const struct sockaddr_in *host4 = (const struct sockaddr_in *)host;
#ifndef NOINET6
  const struct sockaddr_in6 *host6 = (const struct sockaddr_in6 *)host;
#endif

  switch (host->sa_family) {
  case AF_INET:
    addr->ncpaddr_family = AF_INET;
    addr->ncpaddr_ip4addr = host4->sin_addr;
    break;

#ifndef NOINET6
  case AF_INET6:
    if (IN6_IS_ADDR_V4MAPPED(&host6->sin6_addr)) {
      addr->ncpaddr_family = AF_INET;
      addr->ncpaddr_ip4addr.s_addr =
        *(const u_int32_t *)(host6->sin6_addr.s6_addr + 12);
    } else {
      addr->ncpaddr_family = AF_INET6;
      addr->ncpaddr_ip6addr = host6->sin6_addr;
    }
    break;
#endif

  default:
    addr->ncpaddr_family = AF_UNSPEC;
  }
}