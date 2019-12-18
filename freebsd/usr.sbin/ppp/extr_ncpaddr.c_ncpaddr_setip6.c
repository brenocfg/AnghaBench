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
struct ncpaddr {struct in6_addr ncpaddr_ip6addr; int /*<<< orphan*/  ncpaddr_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 

void
ncpaddr_setip6(struct ncpaddr *addr, const struct in6_addr *ip6)
{
  addr->ncpaddr_family = AF_INET6;
  addr->ncpaddr_ip6addr = *ip6;
}