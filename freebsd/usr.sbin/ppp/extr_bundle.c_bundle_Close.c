#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct datalink {scalar_t__ state; struct datalink* next; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  mp; } ;
struct TYPE_5__ {scalar_t__ sessiontime; } ;
struct bundle {struct datalink* links; TYPE_2__ ncp; TYPE_1__ radius; } ;

/* Variables and functions */
#define  CLOSE_LCP 129 
#define  CLOSE_STAYDOWN 128 
 scalar_t__ DATALINK_CLOSED ; 
 scalar_t__ DATALINK_HANGUP ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  bundle_StopIdleTimer (struct bundle*) ; 
 int /*<<< orphan*/  bundle_StopSessionTimer (struct bundle*) ; 
 int /*<<< orphan*/  datalink_Close (struct datalink*,int) ; 
 int /*<<< orphan*/  datalink_DontHangup (struct datalink*) ; 
 int /*<<< orphan*/  datalink_StayDown (struct datalink*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mp_Down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp2initial (TYPE_2__*) ; 
 int /*<<< orphan*/  ncp_Close (TYPE_2__*) ; 
 scalar_t__ ncp_LayersUnfinished (TYPE_2__*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

void
bundle_Close(struct bundle *bundle, const char *name, int how)
{
  /*
   * Please close the given datalink.
   * If name == NULL or name is the last datalink, fsm_Close all NCPs
   * (except our MP)
   * If it isn't the last datalink, just Close that datalink.
   */

  struct datalink *dl, *this_dl;
  int others_active;

  others_active = 0;
  this_dl = NULL;

  for (dl = bundle->links; dl; dl = dl->next) {
    if (name && !strcasecmp(name, dl->name))
      this_dl = dl;
    if (name == NULL || this_dl == dl) {
      switch (how) {
        case CLOSE_LCP:
          datalink_DontHangup(dl);
          break;
        case CLOSE_STAYDOWN:
          datalink_StayDown(dl);
          break;
      }
    } else if (dl->state != DATALINK_CLOSED && dl->state != DATALINK_HANGUP)
      others_active++;
  }

  if (name && this_dl == NULL) {
    log_Printf(LogWARN, "%s: Invalid datalink name\n", name);
    return;
  }

  if (!others_active) {
#ifndef NORADIUS
    if (bundle->radius.sessiontime)
      bundle_StopSessionTimer(bundle);
#endif
    bundle_StopIdleTimer(bundle);
    if (ncp_LayersUnfinished(&bundle->ncp))
      ncp_Close(&bundle->ncp);
    else {
      ncp2initial(&bundle->ncp);
      mp_Down(&bundle->ncp.mp);
      for (dl = bundle->links; dl; dl = dl->next)
        datalink_Close(dl, how);
    }
  } else if (this_dl && this_dl->state != DATALINK_CLOSED &&
             this_dl->state != DATALINK_HANGUP)
    datalink_Close(this_dl, how);
}