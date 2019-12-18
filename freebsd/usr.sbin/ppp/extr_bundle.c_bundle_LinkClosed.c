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
struct datalink {scalar_t__ state; TYPE_1__* physical; struct datalink* next; } ;
struct TYPE_5__ {scalar_t__ sessiontime; } ;
struct TYPE_6__ {int /*<<< orphan*/  mp; } ;
struct bundle {TYPE_2__ radius; TYPE_3__ ncp; struct datalink* links; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DATALINK_CLOSED ; 
 int /*<<< orphan*/  PHASE_DEAD ; 
 scalar_t__ PHYS_AUTO ; 
 int /*<<< orphan*/  bundle_DownInterface (struct bundle*) ; 
 int /*<<< orphan*/  bundle_NewPhase (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_StopIdleTimer (struct bundle*) ; 
 int /*<<< orphan*/  bundle_StopSessionTimer (struct bundle*) ; 
 int /*<<< orphan*/  log_SetTtyCommandMode (struct datalink*) ; 
 int /*<<< orphan*/  mp_Down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp2initial (TYPE_3__*) ; 

void
bundle_LinkClosed(struct bundle *bundle, struct datalink *dl)
{
  /*
   * Our datalink has closed.
   * CleanDatalinks() (called from DoLoop()) will remove closed
   * BACKGROUND, FOREGROUND and DIRECT links.
   * If it's the last data link, enter phase DEAD.
   *
   * NOTE: dl may not be in our list (bundle_SendDatalink()) !
   */

  struct datalink *odl;
  int other_links;

  log_SetTtyCommandMode(dl);

  other_links = 0;
  for (odl = bundle->links; odl; odl = odl->next)
    if (odl != dl && odl->state != DATALINK_CLOSED)
      other_links++;

  if (!other_links) {
    if (dl->physical->type != PHYS_AUTO)	/* Not in -auto mode */
      bundle_DownInterface(bundle);
    ncp2initial(&bundle->ncp);
    mp_Down(&bundle->ncp.mp);
    bundle_NewPhase(bundle, PHASE_DEAD);
#ifndef NORADIUS
    if (bundle->radius.sessiontime)
      bundle_StopSessionTimer(bundle);
#endif
    bundle_StopIdleTimer(bundle);
  }
}