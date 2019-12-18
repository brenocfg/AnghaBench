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
struct datalink {struct datalink* next; } ;
struct TYPE_5__ {scalar_t__ sessiontime; } ;
struct TYPE_6__ {int all; int open; } ;
struct TYPE_4__ {int /*<<< orphan*/  mp; } ;
struct bundle {TYPE_2__ radius; TYPE_3__ phys_type; TYPE_1__ ncp; struct datalink* links; } ;

/* Variables and functions */
 int PHYS_DDIAL ; 
 int PHYS_DEDICATED ; 
 int /*<<< orphan*/  bundle_CalculateBandwidth (struct bundle*) ; 
 int /*<<< orphan*/  bundle_LinkAdded (struct bundle*,struct datalink*) ; 
 int /*<<< orphan*/  bundle_StopIdleTimer (struct bundle*) ; 
 int /*<<< orphan*/  bundle_StopSessionTimer (struct bundle*) ; 
 int /*<<< orphan*/  mp_CheckAutoloadTimer (int /*<<< orphan*/ *) ; 

void
bundle_LinksRemoved(struct bundle *bundle)
{
  struct datalink *dl;

  bundle->phys_type.all = bundle->phys_type.open = 0;
  for (dl = bundle->links; dl; dl = dl->next)
    bundle_LinkAdded(bundle, dl);

  bundle_CalculateBandwidth(bundle);
  mp_CheckAutoloadTimer(&bundle->ncp.mp);

  if ((bundle->phys_type.open & (PHYS_DEDICATED|PHYS_DDIAL))
      == bundle->phys_type.open) {
#ifndef NORADIUS
    if (bundle->radius.sessiontime)
      bundle_StopSessionTimer(bundle);
#endif
    bundle_StopIdleTimer(bundle);
   }
}