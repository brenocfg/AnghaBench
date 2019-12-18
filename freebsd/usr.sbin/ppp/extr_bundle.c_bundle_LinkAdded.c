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
struct datalink {scalar_t__ state; TYPE_1__* physical; } ;
struct TYPE_13__ {scalar_t__ state; } ;
struct TYPE_14__ {TYPE_6__ timer; } ;
struct TYPE_12__ {int all; int open; } ;
struct TYPE_11__ {scalar_t__ sessiontime; } ;
struct TYPE_9__ {scalar_t__ state; } ;
struct TYPE_10__ {TYPE_2__ timer; } ;
struct bundle {TYPE_7__ idle; TYPE_5__ phys_type; TYPE_4__ radius; TYPE_3__ session; } ;
struct TYPE_8__ {int type; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPEN ; 
 int PHYS_DDIAL ; 
 int PHYS_DEDICATED ; 
 scalar_t__ TIMER_STOPPED ; 
 int /*<<< orphan*/  bundle_StartIdleTimer (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_StartSessionTimer (struct bundle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bundle_LinkAdded(struct bundle *bundle, struct datalink *dl)
{
  bundle->phys_type.all |= dl->physical->type;
  if (dl->state == DATALINK_OPEN)
    bundle->phys_type.open |= dl->physical->type;

#ifndef NORADIUS
  if ((bundle->phys_type.open & (PHYS_DEDICATED|PHYS_DDIAL))
      != bundle->phys_type.open && bundle->session.timer.state == TIMER_STOPPED)
    if (bundle->radius.sessiontime)
      bundle_StartSessionTimer(bundle, 0);
#endif

  if ((bundle->phys_type.open & (PHYS_DEDICATED|PHYS_DDIAL))
      != bundle->phys_type.open && bundle->idle.timer.state == TIMER_STOPPED)
    /* We may need to start our idle timer */
    bundle_StartIdleTimer(bundle, 0);
}