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
struct ncp {int /*<<< orphan*/  ipv6cp; int /*<<< orphan*/  ipcp; } ;
struct iface_addr {int /*<<< orphan*/  ifa; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ipcp_IfaceAddrAdded (int /*<<< orphan*/ *,struct iface_addr const*) ; 
 int /*<<< orphan*/  ipv6cp_IfaceAddrAdded (int /*<<< orphan*/ *,struct iface_addr const*) ; 
 int ncprange_family (int /*<<< orphan*/ *) ; 

void
ncp_IfaceAddrAdded(struct ncp *ncp, const struct iface_addr *addr)
{
  switch (ncprange_family(&addr->ifa)) {
  case AF_INET:
    ipcp_IfaceAddrAdded(&ncp->ipcp, addr);
    break;
#ifndef NOINET6
  case AF_INET6:
    ipv6cp_IfaceAddrAdded(&ncp->ipv6cp, addr);
    break;
#endif
  }
}