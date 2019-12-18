#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct swapent {int se_flags; int se_inuse; int se_nblks; } ;
struct TYPE_5__ {unsigned long long total; unsigned long long* values; scalar_t__ pl; } ;
struct TYPE_4__ {unsigned long long totalSwap; unsigned long long usedSwap; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ Meter ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int /*<<< orphan*/  SWAP_NSWAP ; 
 int /*<<< orphan*/  SWAP_STATS ; 
 int SWF_ENABLE ; 
 int /*<<< orphan*/  free (struct swapent*) ; 
 int swapctl (int /*<<< orphan*/ ,struct swapent*,int) ; 
 struct swapent* xCalloc (int,int) ; 

void Platform_setSwapValues(Meter* this) {
   ProcessList* pl = (ProcessList*) this->pl;
   struct swapent *swdev;
   unsigned long long int total, used;
   int nswap, rnswap, i;
   nswap = swapctl(SWAP_NSWAP, 0, 0);
   if (nswap == 0) {
      return;
   }

   swdev = xCalloc(nswap, sizeof(*swdev));

   rnswap = swapctl(SWAP_STATS, swdev, nswap);
   if (rnswap == -1) {
      free(swdev);
      return;
   }

   // if rnswap != nswap, then what?

   /* Total things up */
   total = used = 0;
   for (i = 0; i < nswap; i++) {
      if (swdev[i].se_flags & SWF_ENABLE) {
         used += (swdev[i].se_inuse / (1024 / DEV_BSIZE));
         total += (swdev[i].se_nblks / (1024 / DEV_BSIZE));
      }
   }

   this->total = pl->totalSwap = total;
   this->values[0] = pl->usedSwap = used;

   free(swdev);
}