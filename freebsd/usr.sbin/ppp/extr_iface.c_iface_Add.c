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
struct ncprange {int dummy; } ;
struct ncpaddr {int dummy; } ;
struct ncp {int dummy; } ;
struct iface_addr {int system; int /*<<< orphan*/  peer; int /*<<< orphan*/  ifa; } ;
struct iface {unsigned int addrs; struct iface_addr* addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ID0socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFACE_ADD_FIRST ; 
 int IFACE_FORCE_ADD ; 
 int IFACE_SYSTEM ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bcopy (struct iface_addr*,struct iface_addr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  iface_addr_Add (int /*<<< orphan*/ ,struct iface_addr*,int) ; 
 int iface_addr_Zap (int /*<<< orphan*/ ,struct iface_addr*,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct iface_addr*,struct iface_addr*,int) ; 
 int /*<<< orphan*/  ncp_IfaceAddrAdded (struct ncp*,struct iface_addr*) ; 
 int /*<<< orphan*/  ncp_IfaceAddrDeleted (struct ncp*,struct iface_addr*) ; 
 int /*<<< orphan*/  ncpaddr_copy (int /*<<< orphan*/ *,struct ncpaddr const*) ; 
 scalar_t__ ncpaddr_equal (int /*<<< orphan*/ *,struct ncpaddr const*) ; 
 scalar_t__ ncprange_contains (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_copy (int /*<<< orphan*/ *,struct ncprange const*) ; 
 scalar_t__ ncprange_equal (int /*<<< orphan*/ *,struct ncprange const*) ; 
 int ncprange_family (struct ncprange const*) ; 
 int /*<<< orphan*/  ncprange_getaddr (struct ncprange const*,struct ncpaddr*) ; 
 scalar_t__ realloc (struct iface_addr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
iface_Add(struct iface *iface, struct ncp *ncp, const struct ncprange *ifa,
          const struct ncpaddr *peer, int how)
{
  int af, removed, s;
  unsigned n;
  struct ncpaddr ncplocal;
  struct iface_addr *addr, newaddr;

  af = ncprange_family(ifa);
  if ((s = ID0socket(af, SOCK_DGRAM, 0)) == -1) {
    log_Printf(LogERROR, "iface_Add: socket(): %s\n", strerror(errno));
    return 0;
  }
  ncprange_getaddr(ifa, &ncplocal);

  for (n = 0; n < iface->addrs; n++) {
    if (ncprange_contains(&iface->addr[n].ifa, &ncplocal) ||
        ncpaddr_equal(&iface->addr[n].peer, peer)) {
      /* Replace this sockaddr */
      if (!(how & IFACE_FORCE_ADD)) {
        close(s);
        return 0;	/* errno = EEXIST; */
      }

      if (ncprange_equal(&iface->addr[n].ifa, ifa) &&
          ncpaddr_equal(&iface->addr[n].peer, peer)) {
        close(s);
        ncp_IfaceAddrAdded(ncp, iface->addr + n);
        return 1;	/* Already there */
      }

      removed = iface_addr_Zap(iface->name, iface->addr + n, s);
      if (removed)
        ncp_IfaceAddrDeleted(ncp, iface->addr + n);
      ncprange_copy(&iface->addr[n].ifa, ifa);
      ncpaddr_copy(&iface->addr[n].peer, peer);
      if (!iface_addr_Add(iface->name, iface->addr + n, s)) {
        if (removed) {
          bcopy(iface->addr + n + 1, iface->addr + n,
                (iface->addrs - n - 1) * sizeof *iface->addr);
          iface->addrs--;
          n--;
        }
        close(s);
        return 0;
      }
      close(s);
      ncp_IfaceAddrAdded(ncp, iface->addr + n);
      return 1;
    }
  }

  addr = (struct iface_addr *)realloc
    (iface->addr, (iface->addrs + 1) * sizeof iface->addr[0]);
  if (addr == NULL) {
    log_Printf(LogERROR, "iface_inAdd: realloc: %s\n", strerror(errno));
    close(s);
    return 0;
  }
  iface->addr = addr;

  ncprange_copy(&newaddr.ifa, ifa);
  ncpaddr_copy(&newaddr.peer, peer);
  newaddr.system = !!(how & IFACE_SYSTEM);
  if (!iface_addr_Add(iface->name, &newaddr, s)) {
    close(s);
    return 0;
  }

  if (how & IFACE_ADD_FIRST) {
    /* Stuff it at the start of our list */
    n = 0;
    bcopy(iface->addr, iface->addr + 1, iface->addrs * sizeof *iface->addr);
  } else
    n = iface->addrs;

  iface->addrs++;
  memcpy(iface->addr + n, &newaddr, sizeof(*iface->addr));

  close(s);
  ncp_IfaceAddrAdded(ncp, iface->addr + n);

  return 1;
}