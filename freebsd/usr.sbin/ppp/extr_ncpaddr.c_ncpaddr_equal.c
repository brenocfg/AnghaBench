#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct ncpaddr {int ncpaddr_family; int /*<<< orphan*/  ncpaddr_ip6addr; TYPE_1__ ncpaddr_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
ncpaddr_equal(const struct ncpaddr *addr, const struct ncpaddr *cmp)
{
  if (addr->ncpaddr_family != cmp->ncpaddr_family)
    return 0;

  switch (addr->ncpaddr_family) {
  case AF_INET:
    return addr->ncpaddr_ip4addr.s_addr == cmp->ncpaddr_ip4addr.s_addr;

#ifndef NOINET6
  case AF_INET6:
    return !memcmp(&addr->ncpaddr_ip6addr, &cmp->ncpaddr_ip6addr,
                   sizeof addr->ncpaddr_ip6addr);
#endif

  case AF_UNSPEC:
    return 1;
  }

  return 0;
}