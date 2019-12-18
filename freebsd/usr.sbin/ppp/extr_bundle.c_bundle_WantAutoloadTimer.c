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
struct datalink {scalar_t__ state; TYPE_1__* physical; struct datalink* next; } ;
struct bundle {scalar_t__ phase; struct datalink* links; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPEN ; 
 scalar_t__ PHASE_NETWORK ; 
 scalar_t__ PHYS_AUTO ; 

int
bundle_WantAutoloadTimer(struct bundle *bundle)
{
  struct datalink *dl;
  int autolink, opened;

  if (bundle->phase == PHASE_NETWORK) {
    for (autolink = opened = 0, dl = bundle->links; dl; dl = dl->next)
      if (dl->physical->type == PHYS_AUTO) {
        if (++autolink == 2 || (autolink == 1 && opened))
          /* Two auto links or one auto and one open in NETWORK phase */
          return 1;
      } else if (dl->state == DATALINK_OPEN) {
        opened++;
        if (autolink)
          /* One auto and one open link in NETWORK phase */
          return 1;
      }
  }

  return 0;
}