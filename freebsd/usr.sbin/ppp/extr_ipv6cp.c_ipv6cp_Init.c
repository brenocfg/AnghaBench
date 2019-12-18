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
struct link {int dummy; } ;
struct TYPE_4__ {void* maxtrm; void* maxreq; int /*<<< orphan*/  timeout; } ;
struct TYPE_5__ {TYPE_1__ fsm; } ;
struct ipv6cp {int /*<<< orphan*/  Queue; int /*<<< orphan*/  throughput; int /*<<< orphan*/  my_ifid; int /*<<< orphan*/  his_ifid; TYPE_2__ cfg; int /*<<< orphan*/  fsm; } ;
struct fsm_parent {int dummy; } ;
struct bundle {int dummy; } ;
struct TYPE_6__ {scalar_t__ ipv6_available; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FSMRETRY ; 
 void* DEF_FSMTRIES ; 
 int /*<<< orphan*/  IPV6CP_IFIDLEN ; 
 int /*<<< orphan*/  IPV6CP_MAXCODE ; 
 int /*<<< orphan*/  LogIPV6CP ; 
 int /*<<< orphan*/  PROTO_IPV6CP ; 
 int /*<<< orphan*/  SAMPLE_PERIOD ; 
 int /*<<< orphan*/  SetInterfaceID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsm_Init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bundle*,struct link*,struct fsm_parent const*,int /*<<< orphan*/ *,char const* const*) ; 
 int /*<<< orphan*/  ipcp_SetIPv6address (struct ipv6cp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6cp_Callbacks ; 
 int /*<<< orphan*/  ipv6cp_Setup (struct ipv6cp*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 TYPE_3__ probe ; 
 int /*<<< orphan*/  throughput_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ipv6cp_Init(struct ipv6cp *ipv6cp, struct bundle *bundle, struct link *l,
                 const struct fsm_parent *parent)
{
  static const char * const timer_names[] =
    {"IPV6CP restart", "IPV6CP openmode", "IPV6CP stopped"};
  int n;

  fsm_Init(&ipv6cp->fsm, "IPV6CP", PROTO_IPV6CP, 1, IPV6CP_MAXCODE, LogIPV6CP,
           bundle, l, parent, &ipv6cp_Callbacks, timer_names);

  ipv6cp->cfg.fsm.timeout = DEF_FSMRETRY;
  ipv6cp->cfg.fsm.maxreq = DEF_FSMTRIES;
  ipv6cp->cfg.fsm.maxtrm = DEF_FSMTRIES;

  SetInterfaceID(ipv6cp->my_ifid, 0);
  do {
    SetInterfaceID(ipv6cp->his_ifid, 1);
  } while (memcmp(ipv6cp->his_ifid, ipv6cp->my_ifid, IPV6CP_IFIDLEN) == 0);

  if (probe.ipv6_available) {
    n = 100;
    while (n &&
           !ipcp_SetIPv6address(ipv6cp, ipv6cp->my_ifid, ipv6cp->his_ifid)) {
      do {
	n--;
    	SetInterfaceID(ipv6cp->my_ifid, 1);
      } while (n
	&& memcmp(ipv6cp->his_ifid, ipv6cp->my_ifid, IPV6CP_IFIDLEN) == 0);
    }
  }

  throughput_init(&ipv6cp->throughput, SAMPLE_PERIOD);
  memset(ipv6cp->Queue, '\0', sizeof ipv6cp->Queue);
  ipv6cp_Setup(ipv6cp);
}