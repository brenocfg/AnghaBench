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
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 

int
ncpaddr_isdefault(const struct ncpaddr *addr)
{
  switch (addr->ncpaddr_family) {
  case AF_INET:
    if (addr->ncpaddr_ip4addr.s_addr == INADDR_ANY)
      return 1;
    break;

#ifndef NOINET6
  case AF_INET6:
    if (IN6_IS_ADDR_UNSPECIFIED(&addr->ncpaddr_ip6addr))
      return 1;
    break;
#endif
  }

  return 0;
}