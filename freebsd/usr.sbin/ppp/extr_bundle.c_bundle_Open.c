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
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {TYPE_3__ timer; } ;
struct datalink {scalar_t__ state; TYPE_2__ dial; TYPE_1__* physical; int /*<<< orphan*/  name; struct datalink* next; } ;
struct bundle {struct datalink* links; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 scalar_t__ DATALINK_CLOSED ; 
 scalar_t__ DATALINK_OPENING ; 
 scalar_t__ DATALINK_READY ; 
 int PHYS_AUTO ; 
 scalar_t__ TIMER_RUNNING ; 
 int /*<<< orphan*/  datalink_Up (struct datalink*,int,int) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_3__*) ; 

void
bundle_Open(struct bundle *bundle, const char *name, int mask, int force)
{
  /*
   * Please open the given datalink, or all if name == NULL
   */
  struct datalink *dl;

  for (dl = bundle->links; dl; dl = dl->next)
    if (name == NULL || !strcasecmp(dl->name, name)) {
      if ((mask & dl->physical->type) &&
          (dl->state == DATALINK_CLOSED ||
           (force && dl->state == DATALINK_OPENING &&
            dl->dial.timer.state == TIMER_RUNNING) ||
           dl->state == DATALINK_READY)) {
        timer_Stop(&dl->dial.timer);	/* We're finished with this */
        datalink_Up(dl, 1, 1);
        if (mask & PHYS_AUTO)
          break;			/* Only one AUTO link at a time */
      }
      if (name != NULL)
        break;
    }
}