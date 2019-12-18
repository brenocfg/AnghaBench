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
struct in_addr {int dummy; } ;
struct ncpaddr {scalar_t__ ncpaddr_family; struct in_addr ncpaddr_ip4addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 

int
ncpaddr_getip4(const struct ncpaddr *addr, struct in_addr *ip)
{
  if (addr->ncpaddr_family != AF_INET)
    return 0;
  *ip = addr->ncpaddr_ip4addr;
  return 1;
}