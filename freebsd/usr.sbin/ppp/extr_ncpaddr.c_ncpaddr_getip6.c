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
struct in6_addr {int dummy; } ;
struct ncpaddr {scalar_t__ ncpaddr_family; struct in6_addr ncpaddr_ip6addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 

int
ncpaddr_getip6(const struct ncpaddr *addr, struct in6_addr *ip6)
{
  if (addr->ncpaddr_family != AF_INET6)
    return 0;
  *ip6 = addr->ncpaddr_ip6addr;
  return 1;
}