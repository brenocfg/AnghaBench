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
struct datalink {scalar_t__ state; struct datalink* next; TYPE_1__* physical; } ;
struct bundle {struct datalink* links; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 scalar_t__ DATALINK_CLOSED ; 
 int PHYS_BACKGROUND ; 
 int PHYS_DIRECT ; 
 int PHYS_FOREGROUND ; 
 int /*<<< orphan*/  bundle_LinksRemoved (struct bundle*) ; 
 struct datalink* datalink_Destroy (struct datalink*) ; 

void
bundle_CleanDatalinks(struct bundle *bundle)
{
  struct datalink **dlp = &bundle->links;
  int found = 0;

  while (*dlp)
    if ((*dlp)->state == DATALINK_CLOSED &&
        (*dlp)->physical->type &
        (PHYS_DIRECT|PHYS_BACKGROUND|PHYS_FOREGROUND)) {
      *dlp = datalink_Destroy(*dlp);
      found++;
    } else
      dlp = &(*dlp)->next;

  if (found)
    bundle_LinksRemoved(bundle);
}