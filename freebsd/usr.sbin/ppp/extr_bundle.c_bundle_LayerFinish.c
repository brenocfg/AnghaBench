#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsm {int /*<<< orphan*/  proto; } ;
struct datalink {scalar_t__ state; struct datalink* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  mp; } ;
struct bundle {TYPE_1__ ncp; struct datalink* links; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 scalar_t__ DATALINK_OPEN ; 
 scalar_t__ PHASE_DEAD ; 
 int /*<<< orphan*/  PHASE_TERMINATE ; 
 int /*<<< orphan*/  bundle_NewPhase (struct bundle*,int /*<<< orphan*/ ) ; 
 scalar_t__ bundle_Phase (struct bundle*) ; 
 int /*<<< orphan*/  datalink_Close (struct datalink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm2initial (struct fsm*) ; 
 scalar_t__ isncp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_Down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_LayersUnfinished (TYPE_1__*) ; 

__attribute__((used)) static void
bundle_LayerFinish(void *v, struct fsm *fp)
{
  /* The given fsm is now down (fp cannot be NULL)
   *
   * If it's the last NCP, fsm_Close all LCPs
   * If it's the last NCP, bring any MP layer down
   */

  struct bundle *bundle = (struct bundle *)v;
  struct datalink *dl;

  if (isncp(fp->proto) && !ncp_LayersUnfinished(&bundle->ncp)) {
    if (bundle_Phase(bundle) != PHASE_DEAD)
      bundle_NewPhase(bundle, PHASE_TERMINATE);
    for (dl = bundle->links; dl; dl = dl->next)
      if (dl->state == DATALINK_OPEN)
        datalink_Close(dl, CLOSE_STAYDOWN);
    fsm2initial(fp);
    mp_Down(&bundle->ncp.mp);
  }
}