#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; scalar_t__ sin6_family; TYPE_1__ sin_addr; } ;
struct TYPE_4__ {void* ia6t_pltime; void* ia6t_vltime; } ;
struct in6_aliasreq {char const* ifra_name; TYPE_2__ ifra_lifetime; struct sockaddr_in ifra_dstaddr; struct sockaddr_in ifra_prefixmask; struct sockaddr_in ifra_addr; int /*<<< orphan*/  ifra_broadaddr; int /*<<< orphan*/  ifra_mask; } ;
struct ifaliasreq {char const* ifra_name; TYPE_2__ ifra_lifetime; struct sockaddr_in ifra_dstaddr; struct sockaddr_in ifra_prefixmask; struct sockaddr_in ifra_addr; int /*<<< orphan*/  ifra_broadaddr; int /*<<< orphan*/  ifra_mask; } ;
struct iface_addr {int /*<<< orphan*/  ifa; int /*<<< orphan*/  peer; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ AF_UNSPEC ; 
 int ID0ioctl (int,int /*<<< orphan*/ ,struct in6_aliasreq*) ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 int NCP_ASCIIBUFFERSIZE ; 
 void* ND6_INFINITE_LIFETIME ; 
 int /*<<< orphan*/  SIOCAIFADDR ; 
 int /*<<< orphan*/  SIOCAIFADDR_IN6 ; 
 int errno ; 
 int /*<<< orphan*/  in6mask128 ; 
 int /*<<< orphan*/  log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in*,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  memset (struct in6_aliasreq*,char,int) ; 
 scalar_t__ ncpaddr_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncpaddr_getsa (int /*<<< orphan*/ *,struct sockaddr_storage*) ; 
 char* ncpaddr_ntoa (int /*<<< orphan*/ *) ; 
 int const ncprange_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncprange_getsa (int /*<<< orphan*/ *,struct sockaddr_storage*,struct sockaddr_storage*) ; 
 char* ncprange_ntoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strerror (int) ; 
 int /*<<< orphan*/  strncpy (char const*,char const*,int) ; 

__attribute__((used)) static int
iface_addr_Add(const char *name, struct iface_addr *addr, int s)
{
  struct ifaliasreq ifra;
#ifndef NOINET6
  struct in6_aliasreq ifra6;
#endif
  struct sockaddr_in *me4, *msk4, *peer4;
  struct sockaddr_storage ssme, sspeer, ssmsk;
  int res, saved_errno;

  ncprange_getsa(&addr->ifa, &ssme, &ssmsk);
  ncpaddr_getsa(&addr->peer, &sspeer);
  res = 0;

  switch (ncprange_family(&addr->ifa)) {
  case AF_INET:
    memset(&ifra, '\0', sizeof ifra);
    strncpy(ifra.ifra_name, name, sizeof ifra.ifra_name - 1);

    me4 = (struct sockaddr_in *)&ifra.ifra_addr;
    memcpy(me4, &ssme, sizeof *me4);

    msk4 = (struct sockaddr_in *)&ifra.ifra_mask;
    memcpy(msk4, &ssmsk, sizeof *msk4);

    peer4 = (struct sockaddr_in *)&ifra.ifra_broadaddr;
    if (ncpaddr_family(&addr->peer) == AF_UNSPEC) {
      peer4->sin_family = AF_INET;
      peer4->sin_len = sizeof(*peer4);
      peer4->sin_addr.s_addr = INADDR_NONE;
    } else
      memcpy(peer4, &sspeer, sizeof *peer4);

    res = ID0ioctl(s, SIOCAIFADDR, &ifra);
    saved_errno = errno;
    if (log_IsKept(LogDEBUG)) {
      char buf[NCP_ASCIIBUFFERSIZE];

      snprintf(buf, sizeof buf, "%s", ncprange_ntoa(&addr->ifa));
      log_Printf(LogWARN, "%s: AIFADDR %s -> %s returns %d\n",
                 ifra.ifra_name, buf, ncpaddr_ntoa(&addr->peer), res);
    }
    break;

#ifndef NOINET6
  case AF_INET6:
    memset(&ifra6, '\0', sizeof ifra6);
    strncpy(ifra6.ifra_name, name, sizeof ifra6.ifra_name - 1);

    memcpy(&ifra6.ifra_addr, &ssme, sizeof ifra6.ifra_addr);
    memcpy(&ifra6.ifra_prefixmask, &ssmsk, sizeof ifra6.ifra_prefixmask);
    if (ncpaddr_family(&addr->peer) == AF_UNSPEC)
      ifra6.ifra_dstaddr.sin6_family = AF_UNSPEC;
    else if (memcmp(&((struct sockaddr_in6 *)&ssmsk)->sin6_addr, &in6mask128,
		    sizeof in6mask128) == 0)
      memcpy(&ifra6.ifra_dstaddr, &sspeer, sizeof ifra6.ifra_dstaddr);
    ifra6.ifra_lifetime.ia6t_vltime = ND6_INFINITE_LIFETIME;
    ifra6.ifra_lifetime.ia6t_pltime = ND6_INFINITE_LIFETIME;

    res = ID0ioctl(s, SIOCAIFADDR_IN6, &ifra6);
    saved_errno = errno;
    break;
#endif
  }

  if (res == -1) {
    char dst[NCP_ASCIIBUFFERSIZE];
    const char *end =
#ifndef NOINET6
      ncprange_family(&addr->ifa) == AF_INET6 ? "_IN6" :
#endif
      "";

    if (ncpaddr_family(&addr->peer) == AF_UNSPEC)
      log_Printf(LogWARN, "iface add: ioctl(SIOCAIFADDR%s, %s): %s\n",
                 end, ncprange_ntoa(&addr->ifa), strerror(saved_errno));
    else {
      snprintf(dst, sizeof dst, "%s", ncpaddr_ntoa(&addr->peer));
      log_Printf(LogWARN, "iface add: ioctl(SIOCAIFADDR%s, %s -> %s): %s\n",
                 end, ncprange_ntoa(&addr->ifa), dst, strerror(saved_errno));
    }
  }

  return res != -1;
}