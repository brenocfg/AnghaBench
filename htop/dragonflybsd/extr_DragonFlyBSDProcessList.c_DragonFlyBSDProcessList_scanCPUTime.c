#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double userPercent; double nicePercent; double systemPercent; double irqPercent; double systemAllPercent; double idlePercent; } ;
struct TYPE_6__ {unsigned long* cp_time_n; unsigned long* cp_times_n; unsigned long* cp_time_o; unsigned long* cp_times_o; TYPE_3__* cpus; } ;
struct TYPE_5__ {int cpuCount; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ DragonFlyBSDProcessList ;
typedef  TYPE_3__ CPUData ;

/* Variables and functions */
 int CPUSTATES ; 
 size_t CP_IDLE ; 
 size_t CP_INTR ; 
 size_t CP_NICE ; 
 size_t CP_SYS ; 
 size_t CP_USER ; 
 int /*<<< orphan*/  MIB_kern_cp_time ; 
 int /*<<< orphan*/  MIB_kern_cp_times ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sysctl (int /*<<< orphan*/ ,int,unsigned long*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void DragonFlyBSDProcessList_scanCPUTime(ProcessList* pl) {
   const DragonFlyBSDProcessList* dfpl = (DragonFlyBSDProcessList*) pl;

   int cpus   = pl->cpuCount;   // actual CPU count
   int maxcpu = cpus;           // max iteration (in case we have average + smp)
   int cp_times_offset;

   assert(cpus > 0);

   size_t sizeof_cp_time_array;

   unsigned long     *cp_time_n; // old clicks state
   unsigned long     *cp_time_o; // current clicks state

   unsigned long cp_time_d[CPUSTATES];
   double        cp_time_p[CPUSTATES];

   // get averages or single CPU clicks
   sizeof_cp_time_array = sizeof(unsigned long) * CPUSTATES;
   sysctl(MIB_kern_cp_time, 2, dfpl->cp_time_n, &sizeof_cp_time_array, NULL, 0);

   // get rest of CPUs
   if (cpus > 1) {
       // on smp systems DragonFlyBSD kernel concats all CPU states into one long array in
       // kern.cp_times sysctl OID
       // we store averages in dfpl->cpus[0], and actual cores after that
       maxcpu = cpus + 1;
       sizeof_cp_time_array = cpus * sizeof(unsigned long) * CPUSTATES;
       sysctl(MIB_kern_cp_times, 2, dfpl->cp_times_n, &sizeof_cp_time_array, NULL, 0);
   }

   for (int i = 0; i < maxcpu; i++) {
      if (cpus == 1) {
         // single CPU box
         cp_time_n = dfpl->cp_time_n;
         cp_time_o = dfpl->cp_time_o;
      } else {
         if (i == 0 ) {
           // average
           cp_time_n = dfpl->cp_time_n;
           cp_time_o = dfpl->cp_time_o;
         } else {
           // specific smp cores
           cp_times_offset = i - 1;
           cp_time_n = dfpl->cp_times_n + (cp_times_offset * CPUSTATES);
           cp_time_o = dfpl->cp_times_o + (cp_times_offset * CPUSTATES);
         }
      }

      // diff old vs new
      unsigned long long total_o = 0;
      unsigned long long total_n = 0;
      unsigned long long total_d = 0;
      for (int s = 0; s < CPUSTATES; s++) {
        cp_time_d[s] = cp_time_n[s] - cp_time_o[s];
        total_o += cp_time_o[s];
        total_n += cp_time_n[s];
      }

      // totals
      total_d = total_n - total_o;
      if (total_d < 1 ) total_d = 1;

      // save current state as old and calc percentages
      for (int s = 0; s < CPUSTATES; ++s) {
        cp_time_o[s] = cp_time_n[s];
        cp_time_p[s] = ((double)cp_time_d[s]) / ((double)total_d) * 100;
      }

      CPUData* cpuData = &(dfpl->cpus[i]);
      cpuData->userPercent      = cp_time_p[CP_USER];
      cpuData->nicePercent      = cp_time_p[CP_NICE];
      cpuData->systemPercent    = cp_time_p[CP_SYS];
      cpuData->irqPercent       = cp_time_p[CP_INTR];
      cpuData->systemAllPercent = cp_time_p[CP_SYS] + cp_time_p[CP_INTR];
      // this one is not really used, but we store it anyway
      cpuData->idlePercent      = cp_time_p[CP_IDLE];
   }
}