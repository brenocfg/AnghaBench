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
struct datalink {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  mp; } ;
struct TYPE_7__ {int /*<<< orphan*/  timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; } ;
struct bundle {int /*<<< orphan*/ * iface; TYPE_3__ dev; TYPE_4__ ncp; struct datalink* links; int /*<<< orphan*/  radius; TYPE_2__ choked; TYPE_1__ idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_ERRDEAD ; 
 int /*<<< orphan*/  IFACE_CLEAR_ALL ; 
 int /*<<< orphan*/  bundle_DownInterface (struct bundle*) ; 
 int /*<<< orphan*/  bundle_Notify (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_UnlockTun (struct bundle*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 struct datalink* datalink_Destroy (struct datalink*) ; 
 int /*<<< orphan*/  iface_Clear (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iface_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_Down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_Destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  radius_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

void
bundle_Destroy(struct bundle *bundle)
{
  struct datalink *dl;

  /*
   * Clean up the interface.  We don't really need to do the timer_Stop()s,
   * mp_Down(), iface_Clear() and bundle_DownInterface() unless we're getting
   * out under exceptional conditions such as a descriptor exception.
   */
  timer_Stop(&bundle->idle.timer);
  timer_Stop(&bundle->choked.timer);
  mp_Down(&bundle->ncp.mp);
  iface_Clear(bundle->iface, &bundle->ncp, 0, IFACE_CLEAR_ALL);
  bundle_DownInterface(bundle);

#ifndef NORADIUS
  /* Tell the radius server the bad news */
  radius_Destroy(&bundle->radius);
#endif

  /* Again, these are all DATALINK_CLOSED unless we're abending */
  dl = bundle->links;
  while (dl)
    dl = datalink_Destroy(dl);

  ncp_Destroy(&bundle->ncp);

  close(bundle->dev.fd);
  bundle_UnlockTun(bundle);

  /* In case we never made PHASE_NETWORK */
  bundle_Notify(bundle, EX_ERRDEAD);

  iface_Destroy(bundle->iface);
  bundle->iface = NULL;
}