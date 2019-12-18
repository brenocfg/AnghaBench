#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ncp {int dummy; } ;
struct iface {int addrs; TYPE_1__* addr; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  system; int /*<<< orphan*/  ifa; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int ID0socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFACE_CLEAR_ALL ; 
 int IFACE_SYSTEM ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ iface_addr_Zap (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_IfaceAddrDeleted (struct ncp*,TYPE_1__*) ; 
 int ncprange_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
iface_Clear(struct iface *iface, struct ncp *ncp, int family, int how)
{
  int af, inskip, in6skip, s4 = -1, s6 = -1, *s;
  unsigned n;

  if (iface->addrs) {
    inskip = in6skip = how == IFACE_CLEAR_ALL ? 0 : 1;

    for (n = 0; n < iface->addrs; n++) {
      af = ncprange_family(&iface->addr[n].ifa);
      if (family == 0 || family == af) {
        if (!iface->addr[n].system && (how & IFACE_SYSTEM))
          continue;
        switch (af) {
        case AF_INET:
          if (inskip) {
            inskip = 0;
            continue;
          }
          s = &s4;
          break;

#ifndef NOINET6
        case AF_INET6:
          if (in6skip) {
            in6skip = 0;
            continue;
          }
          s = &s6;
          break;
#endif
        default:
          continue;
        }

        if (*s == -1 && (*s = ID0socket(af, SOCK_DGRAM, 0)) == -1)
          log_Printf(LogERROR, "iface_Clear: socket(): %s\n", strerror(errno));
        else if (iface_addr_Zap(iface->name, iface->addr + n, *s)) {
          ncp_IfaceAddrDeleted(ncp, iface->addr + n);
          bcopy(iface->addr + n + 1, iface->addr + n,
                (iface->addrs - n - 1) * sizeof *iface->addr);
          iface->addrs--;
          n--;
        }
      }
    }

    /* Don't bother realloc()ing - we have little to gain */

    if (s4)
      close(s4);
    if (s6)
      close(s6);
  }
}