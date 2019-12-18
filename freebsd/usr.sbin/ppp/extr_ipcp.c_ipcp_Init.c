#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct link {int dummy; } ;
struct TYPE_14__ {int writable; int /*<<< orphan*/ * resolv_nons; int /*<<< orphan*/ * resolv; } ;
struct TYPE_12__ {int slotcomp; int neg; int /*<<< orphan*/  slots; } ;
struct TYPE_11__ {void* maxtrm; void* maxreq; int /*<<< orphan*/  timeout; } ;
struct TYPE_10__ {TYPE_2__* nbns; scalar_t__ dns_neg; TYPE_1__* dns; } ;
struct in_addr {void* s_addr; } ;
struct TYPE_13__ {TYPE_5__ vj; TYPE_4__ fsm; TYPE_3__ ns; scalar_t__ HaveTriggerAddress; int /*<<< orphan*/  peer_list; struct in_addr netmask; int /*<<< orphan*/  peer_range; int /*<<< orphan*/  my_range; } ;
struct ipcp {int /*<<< orphan*/ * Queue; int /*<<< orphan*/  throughput; TYPE_7__ ns; int /*<<< orphan*/  vj; TYPE_6__ cfg; int /*<<< orphan*/  fsm; } ;
struct hostent {scalar_t__ h_addrtype; int h_length; int /*<<< orphan*/  h_addr; } ;
struct fsm_parent {int dummy; } ;
struct bundle {int dummy; } ;
struct TYPE_9__ {void* s_addr; } ;
struct TYPE_8__ {void* s_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DEF_FSMRETRY ; 
 void* DEF_FSMTRIES ; 
 int /*<<< orphan*/  DEF_VJ_STATES ; 
 void* INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 void* INADDR_NONE ; 
 int /*<<< orphan*/  IPCP_MAXCODE ; 
 int /*<<< orphan*/  LogIPCP ; 
 int MAXHOSTNAMELEN ; 
 int NEG_ACCEPTED ; 
 int NEG_ENABLED ; 
 int /*<<< orphan*/  PROTO_IPCP ; 
 int /*<<< orphan*/  SAMPLE_PERIOD ; 
 int /*<<< orphan*/  fsm_Init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bundle*,struct link*,struct fsm_parent const*,int /*<<< orphan*/ *,char const* const*) ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ gethostname (char*,int) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_Callbacks ; 
 int /*<<< orphan*/  ipcp_LoadDNS (struct ipcp*) ; 
 int /*<<< orphan*/  ipcp_Setup (struct ipcp*,void*) ; 
 int /*<<< orphan*/  iplist_setsrc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  ncprange_setip4 (int /*<<< orphan*/ *,struct in_addr,struct in_addr) ; 
 int /*<<< orphan*/  throughput_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ipcp_Init(struct ipcp *ipcp, struct bundle *bundle, struct link *l,
          const struct fsm_parent *parent)
{
  struct hostent *hp;
  struct in_addr host;
  char name[MAXHOSTNAMELEN];
  static const char * const timer_names[] =
    {"IPCP restart", "IPCP openmode", "IPCP stopped"};

  fsm_Init(&ipcp->fsm, "IPCP", PROTO_IPCP, 1, IPCP_MAXCODE, LogIPCP,
           bundle, l, parent, &ipcp_Callbacks, timer_names);

  ipcp->cfg.vj.slots = DEF_VJ_STATES;
  ipcp->cfg.vj.slotcomp = 1;
  memset(&ipcp->cfg.my_range, '\0', sizeof ipcp->cfg.my_range);

  host.s_addr = htonl(INADDR_LOOPBACK);
  ipcp->cfg.netmask.s_addr = INADDR_ANY;
  if (gethostname(name, sizeof name) == 0) {
    hp = gethostbyname(name);
    if (hp && hp->h_addrtype == AF_INET && hp->h_length == sizeof host.s_addr)
      memcpy(&host.s_addr, hp->h_addr, sizeof host.s_addr);
  }
  ncprange_setip4(&ipcp->cfg.my_range, host, ipcp->cfg.netmask);
  ncprange_setip4(&ipcp->cfg.peer_range, ipcp->cfg.netmask, ipcp->cfg.netmask);

  iplist_setsrc(&ipcp->cfg.peer_list, "");
  ipcp->cfg.HaveTriggerAddress = 0;

  ipcp->cfg.ns.dns[0].s_addr = INADDR_NONE;
  ipcp->cfg.ns.dns[1].s_addr = INADDR_NONE;
  ipcp->cfg.ns.dns_neg = 0;
  ipcp->cfg.ns.nbns[0].s_addr = INADDR_ANY;
  ipcp->cfg.ns.nbns[1].s_addr = INADDR_ANY;

  ipcp->cfg.fsm.timeout = DEF_FSMRETRY;
  ipcp->cfg.fsm.maxreq = DEF_FSMTRIES;
  ipcp->cfg.fsm.maxtrm = DEF_FSMTRIES;
  ipcp->cfg.vj.neg = NEG_ENABLED|NEG_ACCEPTED;

  memset(&ipcp->vj, '\0', sizeof ipcp->vj);

  ipcp->ns.resolv = NULL;
  ipcp->ns.resolv_nons = NULL;
  ipcp->ns.writable = 1;
  ipcp_LoadDNS(ipcp);

  throughput_init(&ipcp->throughput, SAMPLE_PERIOD);
  memset(ipcp->Queue, '\0', sizeof ipcp->Queue);
  ipcp_Setup(ipcp, INADDR_NONE);
}