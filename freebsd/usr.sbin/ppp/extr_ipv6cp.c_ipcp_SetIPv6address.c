#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct ncprange {int dummy; } ;
struct ncpaddr {int dummy; } ;
struct TYPE_6__ {struct bundle* bundle; } ;
struct ipv6cp {struct ncpaddr hisaddr; struct ncpaddr myaddr; TYPE_1__ fsm; } ;
struct in6_addr {int* s6_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ipv6routes; scalar_t__ valid; } ;
struct TYPE_7__ {scalar_t__ sendpipe; scalar_t__ recvpipe; } ;
struct TYPE_9__ {int /*<<< orphan*/  route; TYPE_2__ cfg; } ;
struct bundle {TYPE_3__ radius; TYPE_4__ ncp; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ Enabled (struct bundle*,int /*<<< orphan*/ ) ; 
 int IFACE_ADD_FIRST ; 
 int IFACE_CLEAR_ALIASES ; 
 int IFACE_FORCE_ADD ; 
 int IFACE_SYSTEM ; 
 int /*<<< orphan*/  IPV6CP_IFIDLEN ; 
 int /*<<< orphan*/  OPT_IFACEALIAS ; 
 int /*<<< orphan*/  OPT_SROUTES ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  iface_Add (int /*<<< orphan*/ ,TYPE_4__*,struct ncprange*,struct ncpaddr*,int) ; 
 int /*<<< orphan*/  iface_Clear (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 struct in6_addr in6addr_linklocal_mcast ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,char,int) ; 
 int /*<<< orphan*/  ncpaddr_getsa (struct ncpaddr*,struct sockaddr_storage*) ; 
 scalar_t__ ncpaddr_isset (struct ncpaddr*) ; 
 int /*<<< orphan*/  ncpaddr_setip6 (struct ncpaddr*,struct in6_addr*) ; 
 int /*<<< orphan*/  ncprange_getsa (struct ncprange*,struct sockaddr_storage*,struct sockaddr_storage*) ; 
 int /*<<< orphan*/  ncprange_set (struct ncprange*,struct ncpaddr*,int) ; 
 int /*<<< orphan*/  route_Change (struct bundle*,int /*<<< orphan*/ ,struct ncpaddr*,struct ncpaddr*) ; 
 int /*<<< orphan*/  rt_Set (struct bundle*,int /*<<< orphan*/ ,struct ncprange*,struct ncpaddr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_Update (struct bundle*,struct sockaddr*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipcp_SetIPv6address(struct ipv6cp *ipv6cp, u_char *myifid, u_char *hisifid)
{
  struct bundle *bundle = ipv6cp->fsm.bundle;
  struct in6_addr myaddr, hisaddr;
  struct ncprange myrange, range;
  struct ncpaddr addr;
  struct sockaddr_storage ssdst, ssgw, ssmask;
  struct sockaddr *sadst, *sagw, *samask;

  sadst = (struct sockaddr *)&ssdst;
  sagw = (struct sockaddr *)&ssgw;
  samask = (struct sockaddr *)&ssmask;

  memset(&myaddr, '\0', sizeof myaddr);
  memset(&hisaddr, '\0', sizeof hisaddr);

  myaddr.s6_addr[0] = 0xfe;
  myaddr.s6_addr[1] = 0x80;
  memcpy(&myaddr.s6_addr[8], myifid, IPV6CP_IFIDLEN);
#if 0
  myaddr.s6_addr[8] |= 0x02;	/* set 'universal' bit */
#endif

  hisaddr.s6_addr[0] = 0xfe;
  hisaddr.s6_addr[1] = 0x80;
  memcpy(&hisaddr.s6_addr[8], hisifid, IPV6CP_IFIDLEN);
#if 0
  hisaddr.s6_addr[8] |= 0x02;	/* set 'universal' bit */
#endif

  ncpaddr_setip6(&ipv6cp->myaddr, &myaddr);
  ncpaddr_setip6(&ipv6cp->hisaddr, &hisaddr);
  ncprange_set(&myrange, &ipv6cp->myaddr, 64);

  if (!iface_Add(bundle->iface, &bundle->ncp, &myrange, &ipv6cp->hisaddr,
                 IFACE_ADD_FIRST|IFACE_FORCE_ADD|IFACE_SYSTEM))
    return 0;

  if (!Enabled(bundle, OPT_IFACEALIAS))
    iface_Clear(bundle->iface, &bundle->ncp, AF_INET6,
                IFACE_CLEAR_ALIASES|IFACE_SYSTEM);

  ncpaddr_setip6(&addr, &in6addr_linklocal_mcast);
  ncprange_set(&range, &addr, 32);
  rt_Set(bundle, RTM_ADD, &range, &ipv6cp->myaddr, 1, 0);

  if (bundle->ncp.cfg.sendpipe > 0 || bundle->ncp.cfg.recvpipe > 0) {
    ncprange_getsa(&myrange, &ssgw, &ssmask);
    if (ncpaddr_isset(&ipv6cp->hisaddr))
      ncpaddr_getsa(&ipv6cp->hisaddr, &ssdst);
    else
      sadst = NULL;
    rt_Update(bundle, sadst, sagw, samask, NULL, NULL);
  }

  if (Enabled(bundle, OPT_SROUTES))
    route_Change(bundle, bundle->ncp.route, &ipv6cp->myaddr, &ipv6cp->hisaddr);

#ifndef NORADIUS
  if (bundle->radius.valid)
    route_Change(bundle, bundle->radius.ipv6routes, &ipv6cp->myaddr,
                 &ipv6cp->hisaddr);
#endif

  return 1;	/* Ok */
}