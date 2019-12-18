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
struct TYPE_2__ {struct bundle* bundle; } ;
struct ipcp {TYPE_1__ fsm; } ;
struct iface_addr {int dummy; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 scalar_t__ Enabled (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_PROXY ; 
 int /*<<< orphan*/  OPT_PROXYALL ; 
 int /*<<< orphan*/  arp_SetProxy ; 
 int /*<<< orphan*/  ipcp_proxyarp (struct ipcp*,int /*<<< orphan*/ ,struct iface_addr const*) ; 

void
ipcp_IfaceAddrAdded(struct ipcp *ipcp, const struct iface_addr *addr)
{
  struct bundle *bundle = ipcp->fsm.bundle;

  if (Enabled(bundle, OPT_PROXY) || Enabled(bundle, OPT_PROXYALL))
    ipcp_proxyarp(ipcp, arp_SetProxy, addr);
}