#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int bandwidth; } ;
struct datalink {scalar_t__ state; scalar_t__ name; TYPE_10__* physical; TYPE_1__ mp; struct datalink* next; } ;
struct TYPE_19__ {scalar_t__ mtu; scalar_t__ valid; } ;
struct TYPE_16__ {int /*<<< orphan*/  ccp; } ;
struct TYPE_17__ {scalar_t__ peer_mrru; TYPE_5__ link; scalar_t__ active; } ;
struct TYPE_18__ {TYPE_6__ mp; } ;
struct bundle {int bandwidth; TYPE_9__* iface; TYPE_8__ radius; TYPE_7__ ncp; struct datalink* links; } ;
struct TYPE_20__ {scalar_t__ mtu; } ;
struct TYPE_14__ {scalar_t__ his_mru; } ;
struct TYPE_15__ {TYPE_3__ lcp; int /*<<< orphan*/  ccp; } ;
struct TYPE_13__ {scalar_t__ full; } ;
struct TYPE_11__ {TYPE_4__ link; TYPE_2__ name; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPEN ; 
 scalar_t__ DEF_MRU ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogLCP ; 
 int ccp_MTUOverhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int physical_GetSpeed (TYPE_10__*) ; 
 int /*<<< orphan*/  route_UpdateMTU (struct bundle*) ; 
 int /*<<< orphan*/  tun_configure (struct bundle*) ; 

void
bundle_CalculateBandwidth(struct bundle *bundle)
{
  struct datalink *dl;
  int sp, overhead, maxoverhead;

  bundle->bandwidth = 0;
  bundle->iface->mtu = 0;
  maxoverhead = 0;

  for (dl = bundle->links; dl; dl = dl->next) {
    overhead = ccp_MTUOverhead(&dl->physical->link.ccp);
    if (maxoverhead < overhead)
      maxoverhead = overhead;
    if (dl->state == DATALINK_OPEN) {
      if ((sp = dl->mp.bandwidth) == 0 &&
          (sp = physical_GetSpeed(dl->physical)) == 0)
        log_Printf(LogDEBUG, "%s: %s: Cannot determine bandwidth\n",
                   dl->name, dl->physical->name.full);
      else
        bundle->bandwidth += sp;
      if (!bundle->ncp.mp.active) {
        bundle->iface->mtu = dl->physical->link.lcp.his_mru;
        break;
      }
    }
  }

  if (bundle->bandwidth == 0)
    bundle->bandwidth = 115200;		/* Shrug */

  if (bundle->ncp.mp.active) {
    bundle->iface->mtu = bundle->ncp.mp.peer_mrru;
    overhead = ccp_MTUOverhead(&bundle->ncp.mp.link.ccp);
    if (maxoverhead < overhead)
      maxoverhead = overhead;
  } else if (!bundle->iface->mtu)
    bundle->iface->mtu = DEF_MRU;

#ifndef NORADIUS
  if (bundle->radius.valid && bundle->radius.mtu &&
      bundle->radius.mtu < bundle->iface->mtu) {
    log_Printf(LogLCP, "Reducing MTU to radius value %lu\n",
               bundle->radius.mtu);
    bundle->iface->mtu = bundle->radius.mtu;
  }
#endif

  if (maxoverhead) {
    log_Printf(LogLCP, "Reducing MTU from %lu to %lu (CCP requirement)\n",
               bundle->iface->mtu, bundle->iface->mtu - maxoverhead);
    bundle->iface->mtu -= maxoverhead;
  }

  tun_configure(bundle);

  route_UpdateMTU(bundle);
}