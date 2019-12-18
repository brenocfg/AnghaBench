#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_8__ {int totalPeriod; } ;
struct TYPE_7__ {double* values; scalar_t__ pl; } ;
struct TYPE_6__ {TYPE_3__* cpus; } ;
typedef  TYPE_1__ OpenBSDProcessList ;
typedef  TYPE_2__ Meter ;
typedef  TYPE_3__ CPUData ;

/* Variables and functions */
 int CPUSTATES ; 
 int CTL_KERN ; 
 int KERN_CPTIME2 ; 
 int /*<<< orphan*/  Meter_setItems (TYPE_2__*,int) ; 
 int** old_v ; 
 int /*<<< orphan*/  percentages (int,int*,int*,int*,int*) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

double Platform_setCPUValues(Meter* this, int cpu) {
   int i;
   double perc;

   OpenBSDProcessList* pl = (OpenBSDProcessList*) this->pl;
   CPUData* cpuData = &(pl->cpus[cpu]);
   int64_t new_v[CPUSTATES], diff_v[CPUSTATES], scratch_v[CPUSTATES];
   double *v = this->values;
   size_t size = sizeof(double) * CPUSTATES;
   int mib[] = { CTL_KERN, KERN_CPTIME2, cpu-1 };
   if (sysctl(mib, 3, new_v, &size, NULL, 0) == -1) {
      return 0.;
   }

   // XXX: why?
   cpuData->totalPeriod = 1;

   percentages(CPUSTATES, diff_v, new_v,
         (int64_t *)old_v[cpu-1], scratch_v);

   for (i = 0; i < CPUSTATES; i++) {
      old_v[cpu-1][i] = new_v[i];
      v[i] = diff_v[i] / 10.;
   }

   Meter_setItems(this, 4);

   perc = v[0] + v[1] + v[2] + v[3];

   if (perc <= 100. && perc >= 0.) {
      return perc;
   } else {
      return 0.;
   }
}