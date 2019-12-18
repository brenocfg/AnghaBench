#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ncpaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct iface {int flags; int addrs; TYPE_2__* addr; int /*<<< orphan*/  mtu; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct cmdargs {int /*<<< orphan*/  prompt; TYPE_1__* bundle; } ;
struct TYPE_6__ {int flag; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifa; struct ncpaddr peer; } ;
struct TYPE_4__ {struct iface* iface; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  AF_UNSPEC ; 
 TYPE_3__* if_flags ; 
 struct iface* iface_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iface_Free (struct iface*) ; 
 int /*<<< orphan*/  ncpaddr_family (struct ncpaddr*) ; 
 int /*<<< orphan*/  ncpaddr_ntoa (struct ncpaddr*) ; 
 int ncprange_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncprange_getaddr (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_getip4mask (int /*<<< orphan*/ *,struct in_addr*) ; 
 int /*<<< orphan*/  ncprange_getwidth (int /*<<< orphan*/ *,int*) ; 
 int ncprange_scopeid (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,...) ; 

int
iface_Show(struct cmdargs const *arg)
{
  struct ncpaddr ncpaddr;
  struct iface *iface = arg->bundle->iface, *current;
  unsigned f;
  int flags;
#ifndef NOINET6
  int scopeid, width;
#endif
  struct in_addr mask;

  current = iface_Create(iface->name);
  flags = iface->flags = current->flags;
  iface_Free(current);

  prompt_Printf(arg->prompt, "%s (idx %d) <", iface->name, iface->index);
  for (f = 0; f < sizeof if_flags / sizeof if_flags[0]; f++)
    if ((if_flags[f].flag & flags)) {
      prompt_Printf(arg->prompt, "%s%s", flags == iface->flags ? "" : ",",
                    if_flags[f].value);
      flags &= ~if_flags[f].flag;
    }

#if 0
  if (flags)
    prompt_Printf(arg->prompt, "%s0x%x", flags == iface->flags ? "" : ",",
                  flags);
#endif

  prompt_Printf(arg->prompt, "> mtu %lu has %d address%s:\n", iface->mtu,
                iface->addrs, iface->addrs == 1 ? "" : "es");

  for (f = 0; f < iface->addrs; f++) {
    ncprange_getaddr(&iface->addr[f].ifa, &ncpaddr);
    switch (ncprange_family(&iface->addr[f].ifa)) {
    case AF_INET:
      prompt_Printf(arg->prompt, "  inet %s --> ", ncpaddr_ntoa(&ncpaddr));
      if (ncpaddr_family(&iface->addr[f].peer) == AF_UNSPEC)
        prompt_Printf(arg->prompt, "255.255.255.255");
      else
        prompt_Printf(arg->prompt, "%s", ncpaddr_ntoa(&iface->addr[f].peer));
      ncprange_getip4mask(&iface->addr[f].ifa, &mask);
      prompt_Printf(arg->prompt, " netmask 0x%08lx", (long)ntohl(mask.s_addr));
      break;

#ifndef NOINET6
    case AF_INET6:
      prompt_Printf(arg->prompt, "  inet6 %s", ncpaddr_ntoa(&ncpaddr));
      if (ncpaddr_family(&iface->addr[f].peer) != AF_UNSPEC)
        prompt_Printf(arg->prompt, " --> %s",
                      ncpaddr_ntoa(&iface->addr[f].peer));
      ncprange_getwidth(&iface->addr[f].ifa, &width);
      if (ncpaddr_family(&iface->addr[f].peer) == AF_UNSPEC)
        prompt_Printf(arg->prompt, " prefixlen %d", width);
      if ((scopeid = ncprange_scopeid(&iface->addr[f].ifa)) != -1)
        prompt_Printf(arg->prompt, " scopeid 0x%x", (unsigned)scopeid);
      break;
#endif
    }
    prompt_Printf(arg->prompt, "\n");
  }

  return 0;
}