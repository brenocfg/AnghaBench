#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  size_t u_short ;
struct fdescriptor {int dummy; } ;
struct datalink {int /*<<< orphan*/  desc; struct datalink* next; } ;
struct TYPE_20__ {int /*<<< orphan*/  desc; } ;
struct TYPE_21__ {TYPE_7__ server; } ;
struct TYPE_13__ {TYPE_8__ mp; } ;
struct TYPE_19__ {int /*<<< orphan*/  desc; } ;
struct TYPE_22__ {scalar_t__ state; char* name; int load; struct bundle* arg; int /*<<< orphan*/  func; } ;
struct TYPE_18__ {TYPE_9__ timer; } ;
struct TYPE_16__ {int timeout; } ;
struct TYPE_17__ {int ifqueue; TYPE_3__ choked; } ;
struct TYPE_15__ {int fd; } ;
struct TYPE_14__ {int all; } ;
struct bundle {scalar_t__ phase; TYPE_11__ ncp; struct datalink* links; TYPE_6__ radius; TYPE_5__ choked; TYPE_4__ cfg; TYPE_2__ dev; TYPE_1__ phys_type; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 scalar_t__ PHASE_NETWORK ; 
 int PHYS_AUTO ; 
 int SECTICKS ; 
 scalar_t__ TIMER_RUNNING ; 
 scalar_t__ TIMER_STOPPED ; 
 int /*<<< orphan*/  TUN_NAME ; 
 int /*<<< orphan*/  bundle_ClearQueues ; 
 struct bundle* descriptor2bundle (struct fdescriptor*) ; 
 scalar_t__ descriptor_UpdateSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 size_t ncp_FillPhysicalQueues (TYPE_11__*,struct bundle*) ; 
 size_t ncp_QueueLen (TYPE_11__*) ; 
 int /*<<< orphan*/  timer_Start (TYPE_9__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_9__*) ; 

__attribute__((used)) static int
bundle_UpdateSet(struct fdescriptor *d, fd_set *r, fd_set *w, fd_set *e, int *n)
{
  struct bundle *bundle = descriptor2bundle(d);
  struct datalink *dl;
  int result, nlinks;
  u_short ifqueue;
  size_t queued;

  result = 0;

  /* If there are aren't many packets queued, look for some more. */
  for (nlinks = 0, dl = bundle->links; dl; dl = dl->next)
    nlinks++;

  if (nlinks) {
    queued = r ? ncp_FillPhysicalQueues(&bundle->ncp, bundle) :
                 ncp_QueueLen(&bundle->ncp);

    if (r && (bundle->phase == PHASE_NETWORK ||
              bundle->phys_type.all & PHYS_AUTO)) {
      /* enough surplus so that we can tell if we're getting swamped */
      ifqueue = nlinks > bundle->cfg.ifqueue ? nlinks : bundle->cfg.ifqueue;
      if (queued < ifqueue) {
        /* Not enough - select() for more */
        if (bundle->choked.timer.state == TIMER_RUNNING)
          timer_Stop(&bundle->choked.timer);	/* Not needed any more */
        FD_SET(bundle->dev.fd, r);
        if (*n < bundle->dev.fd + 1)
          *n = bundle->dev.fd + 1;
        log_Printf(LogTIMER, "%s: fdset(r) %d\n", TUN_NAME, bundle->dev.fd);
        result++;
      } else if (bundle->choked.timer.state == TIMER_STOPPED) {
        bundle->choked.timer.func = bundle_ClearQueues;
        bundle->choked.timer.name = "output choke";
        bundle->choked.timer.load = bundle->cfg.choked.timeout * SECTICKS;
        bundle->choked.timer.arg = bundle;
        timer_Start(&bundle->choked.timer);
      }
    }
  }

#ifndef NORADIUS
  result += descriptor_UpdateSet(&bundle->radius.desc, r, w, e, n);
#endif

  /* Which links need a select() ? */
  for (dl = bundle->links; dl; dl = dl->next)
    result += descriptor_UpdateSet(&dl->desc, r, w, e, n);

  /*
   * This *MUST* be called after the datalink UpdateSet()s as it
   * might be ``holding'' one of the datalinks (death-row) and
   * wants to be able to de-select() it from the descriptor set.
   */
  result += descriptor_UpdateSet(&bundle->ncp.mp.server.desc, r, w, e, n);

  return result;
}