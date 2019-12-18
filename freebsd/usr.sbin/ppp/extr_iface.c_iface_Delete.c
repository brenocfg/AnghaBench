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
struct ncpaddr {int dummy; } ;
struct ncp {int dummy; } ;
struct iface {unsigned int addrs; TYPE_1__* addr; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifa; } ;

/* Variables and functions */
 int ID0socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ iface_addr_Zap (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_IfaceAddrDeleted (struct ncp*,TYPE_1__*) ; 
 scalar_t__ ncpaddr_equal (struct ncpaddr*,struct ncpaddr const*) ; 
 int /*<<< orphan*/  ncpaddr_family (struct ncpaddr const*) ; 
 int /*<<< orphan*/  ncprange_getaddr (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
iface_Delete(struct iface *iface, struct ncp *ncp, const struct ncpaddr *del)
{
  struct ncpaddr found;
  unsigned n;
  int res, s;

  if ((s = ID0socket(ncpaddr_family(del), SOCK_DGRAM, 0)) == -1) {
    log_Printf(LogERROR, "iface_Delete: socket(): %s\n", strerror(errno));
    return 0;
  }

  for (n = res = 0; n < iface->addrs; n++) {
    ncprange_getaddr(&iface->addr[n].ifa, &found);
    if (ncpaddr_equal(&found, del)) {
      if (iface_addr_Zap(iface->name, iface->addr + n, s)) {
        ncp_IfaceAddrDeleted(ncp, iface->addr + n);
        bcopy(iface->addr + n + 1, iface->addr + n,
              (iface->addrs - n - 1) * sizeof *iface->addr);
        iface->addrs--;
        res = 1;
      }
      break;
    }
  }

  close(s);

  return res;
}