#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct ncpaddr {int dummy; } ;
struct TYPE_13__ {TYPE_12__* dns; } ;
struct TYPE_23__ {int slots; scalar_t__ slotcomp; int /*<<< orphan*/  neg; } ;
struct in_addr {int dummy; } ;
struct TYPE_17__ {scalar_t__ s_addr; } ;
struct TYPE_14__ {TYPE_10__ ns; TYPE_8__ vj; int /*<<< orphan*/  my_range; struct in_addr TriggerAddress; scalar_t__ HaveTriggerAddress; int /*<<< orphan*/  peer_range; int /*<<< orphan*/  peer_list; TYPE_2__ netmask; } ;
struct TYPE_24__ {int /*<<< orphan*/  dns; } ;
struct TYPE_22__ {int /*<<< orphan*/  cslc; } ;
struct TYPE_21__ {TYPE_5__* bundle; scalar_t__ open_mode; } ;
struct TYPE_16__ {scalar_t__ s_addr; } ;
struct ipcp {TYPE_11__ cfg; TYPE_9__ ns; scalar_t__ my_reject; scalar_t__ peer_reject; TYPE_7__ vj; scalar_t__ my_compproto; TYPE_6__ fsm; struct in_addr my_ip; scalar_t__ peer_compproto; struct in_addr peer_ip; scalar_t__ peer_req; scalar_t__ heis1172; TYPE_1__ ifmask; } ;
struct iface {unsigned int addrs; TYPE_3__* addr; } ;
struct TYPE_19__ {scalar_t__ vj; scalar_t__ valid; } ;
struct TYPE_20__ {TYPE_4__ radius; struct iface* iface; } ;
struct TYPE_18__ {int /*<<< orphan*/  ifa; struct ncpaddr peer; } ;
struct TYPE_15__ {scalar_t__ s_addr; } ;

/* Variables and functions */
 scalar_t__ INADDR_NONE ; 
 scalar_t__ IsEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogIPCP ; 
 int PROTO_VJCOMP ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 int iplist_ip2pos (int /*<<< orphan*/ *,struct in_addr) ; 
 scalar_t__ iplist_isvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iplist_setcurpos (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iplist_setrandpos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_12__*,int) ; 
 int /*<<< orphan*/  ncpaddr_getip4 (struct ncpaddr*,struct in_addr*) ; 
 int /*<<< orphan*/  ncpaddr_setip4 (struct ncpaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ ncprange_contains (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_getaddr (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  ncprange_getip4addr (int /*<<< orphan*/ *,struct in_addr*) ; 
 int /*<<< orphan*/  ncprange_sethost (int /*<<< orphan*/ *,struct ncpaddr*) ; 
 int /*<<< orphan*/  sl_compress_init (int /*<<< orphan*/ *,int) ; 

void
ipcp_Setup(struct ipcp *ipcp, u_int32_t mask)
{
  struct iface *iface = ipcp->fsm.bundle->iface;
  struct ncpaddr ipaddr;
  struct in_addr peer;
  int pos;
  unsigned n;

  ipcp->fsm.open_mode = 0;
  ipcp->ifmask.s_addr = mask == INADDR_NONE ? ipcp->cfg.netmask.s_addr : mask;

  if (iplist_isvalid(&ipcp->cfg.peer_list)) {
    /* Try to give the peer a previously configured IP address */
    for (n = 0; n < iface->addrs; n++) {
      if (!ncpaddr_getip4(&iface->addr[n].peer, &peer))
        continue;
      if ((pos = iplist_ip2pos(&ipcp->cfg.peer_list, peer)) != -1) {
        ncpaddr_setip4(&ipaddr, iplist_setcurpos(&ipcp->cfg.peer_list, pos));
        break;
      }
    }
    if (n == iface->addrs)
      /* Ok, so none of 'em fit.... pick a random one */
      ncpaddr_setip4(&ipaddr, iplist_setrandpos(&ipcp->cfg.peer_list));

    ncprange_sethost(&ipcp->cfg.peer_range, &ipaddr);
  }

  ipcp->heis1172 = 0;
  ipcp->peer_req = 0;
  ncprange_getip4addr(&ipcp->cfg.peer_range, &ipcp->peer_ip);
  ipcp->peer_compproto = 0;

  if (ipcp->cfg.HaveTriggerAddress) {
    /*
     * Some implementations of PPP require that we send a
     * *special* value as our address, even though the rfc specifies
     * full negotiation (e.g. "0.0.0.0" or Not "0.0.0.0").
     */
    ipcp->my_ip = ipcp->cfg.TriggerAddress;
    log_Printf(LogIPCP, "Using trigger address %s\n",
              inet_ntoa(ipcp->cfg.TriggerAddress));
  } else {
    /*
     * Otherwise, if we've used an IP number before and it's still within
     * the network specified on the ``set ifaddr'' line, we really
     * want to keep that IP number so that we can keep any existing
     * connections that are bound to that IP.
     */
    for (n = 0; n < iface->addrs; n++) {
      ncprange_getaddr(&iface->addr[n].ifa, &ipaddr);
      if (ncprange_contains(&ipcp->cfg.my_range, &ipaddr)) {
        ncpaddr_getip4(&ipaddr, &ipcp->my_ip);
        break;
      }
    }
    if (n == iface->addrs)
      ncprange_getip4addr(&ipcp->cfg.my_range, &ipcp->my_ip);
  }

  if (IsEnabled(ipcp->cfg.vj.neg)
#ifndef NORADIUS
      || (ipcp->fsm.bundle->radius.valid && ipcp->fsm.bundle->radius.vj)
#endif
     )
    ipcp->my_compproto = (PROTO_VJCOMP << 16) +
                         ((ipcp->cfg.vj.slots - 1) << 8) +
                         ipcp->cfg.vj.slotcomp;
  else
    ipcp->my_compproto = 0;
  sl_compress_init(&ipcp->vj.cslc, ipcp->cfg.vj.slots - 1);

  ipcp->peer_reject = 0;
  ipcp->my_reject = 0;

  /* Copy startup values into ipcp->ns.dns */
  if (ipcp->cfg.ns.dns[0].s_addr != INADDR_NONE)
    memcpy(ipcp->ns.dns, ipcp->cfg.ns.dns, sizeof ipcp->ns.dns);
}