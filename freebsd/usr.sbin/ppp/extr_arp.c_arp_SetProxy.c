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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr_dl {int /*<<< orphan*/  sdl_alen; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct bundle {int dummy; } ;
struct TYPE_3__ {int sa_len; int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct arpreq {int arp_flags; int /*<<< orphan*/  arp_pa; TYPE_1__ arp_ha; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int ATF_PERM ; 
 int ATF_PUBL ; 
 scalar_t__ ID0ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  LOG_PHASE_BIT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  SET_SA_FAMILY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIOCSARP ; 
 int /*<<< orphan*/  arp_EtherAddr (struct in_addr,struct sockaddr_dl*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct arpreq*,char,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
arp_SetProxy(struct bundle *bundle, struct in_addr addr, int s)
{
  struct arpreq arpreq;
  struct {
    struct sockaddr_dl sdl;
    char space[128];
  }      dls;

  memset(&arpreq, '\0', sizeof arpreq);

  /*
   * Get the hardware address of an interface on the same subnet as our local
   * address.
   */
  if (!arp_EtherAddr(addr, &dls.sdl, 1)) {
    log_Printf(LOG_PHASE_BIT, "Cannot determine ethernet address for "
               "proxy ARP\n");
    return 0;
  }
  arpreq.arp_ha.sa_len = sizeof(struct sockaddr);
  arpreq.arp_ha.sa_family = AF_UNSPEC;
  memcpy(arpreq.arp_ha.sa_data, LLADDR(&dls.sdl), dls.sdl.sdl_alen);
  SET_SA_FAMILY(arpreq.arp_pa, AF_INET);
  ((struct sockaddr_in *)&arpreq.arp_pa)->sin_addr.s_addr = addr.s_addr;
  arpreq.arp_flags = ATF_PERM | ATF_PUBL;
  if (ID0ioctl(s, SIOCSARP, (caddr_t) & arpreq) < 0) {
    log_Printf(LogERROR, "arp_SetProxy: ioctl(SIOCSARP): %s\n",
               strerror(errno));
    return 0;
  }
  return 1;
}