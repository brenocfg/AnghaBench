#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct physical {int /*<<< orphan*/  dl; } ;
struct fsm {scalar_t__ proto; TYPE_4__* bundle; int /*<<< orphan*/  link; } ;
struct TYPE_6__ {scalar_t__ sessiontime; } ;
struct TYPE_5__ {int /*<<< orphan*/  mp; } ;
struct bundle {TYPE_2__ radius; int /*<<< orphan*/  upat; TYPE_1__ ncp; } ;
struct TYPE_7__ {int /*<<< orphan*/  mp; } ;
struct TYPE_8__ {TYPE_3__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_NORMAL ; 
 scalar_t__ PROTO_CCP ; 
 scalar_t__ PROTO_LCP ; 
 int /*<<< orphan*/  bundle_CalculateBandwidth (TYPE_4__*) ; 
 int /*<<< orphan*/  bundle_LinkAdded (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_Notify (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_StartIdleTimer (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_StartSessionTimer (struct bundle*,int /*<<< orphan*/ ) ; 
 scalar_t__ isncp (scalar_t__) ; 
 struct physical* link2physical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_CheckAutoloadTimer (int /*<<< orphan*/ *) ; 
 int ncp_LayersOpen (TYPE_3__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bundle_LayerUp(void *v, struct fsm *fp)
{
  /*
   * The given fsm is now up
   * If it's an LCP, adjust our phys_mode.open value and check the
   * autoload timer.
   * If it's the first NCP, calculate our bandwidth
   * If it's the first NCP, set our ``upat'' time
   * If it's the first NCP, start the idle timer.
   * If it's an NCP, tell our -background parent to go away.
   * If it's the first NCP, start the autoload timer
   */
  struct bundle *bundle = (struct bundle *)v;

  if (fp->proto == PROTO_LCP) {
    struct physical *p = link2physical(fp->link);

    bundle_LinkAdded(bundle, p->dl);
    mp_CheckAutoloadTimer(&bundle->ncp.mp);
  } else if (isncp(fp->proto)) {
    if (ncp_LayersOpen(&fp->bundle->ncp) == 1) {
      bundle_CalculateBandwidth(fp->bundle);
      time(&bundle->upat);
#ifndef NORADIUS
      if (bundle->radius.sessiontime)
        bundle_StartSessionTimer(bundle, 0);
#endif
      bundle_StartIdleTimer(bundle, 0);
      mp_CheckAutoloadTimer(&fp->bundle->ncp.mp);
    }
    bundle_Notify(bundle, EX_NORMAL);
  } else if (fp->proto == PROTO_CCP)
    bundle_CalculateBandwidth(fp->bundle);	/* Against ccp_MTUOverhead */
}