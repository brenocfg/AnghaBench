#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_cpu_load_info_t ;
struct TYPE_9__ {TYPE_1__* curr_load; TYPE_1__* prev_load; } ;
struct TYPE_8__ {double* values; scalar_t__ pl; } ;
struct TYPE_7__ {scalar_t__* cpu_ticks; } ;
typedef  TYPE_2__ Meter ;
typedef  TYPE_3__ DarwinProcessList ;

/* Variables and functions */
 double CLAMP (double,double,double) ; 
 size_t CPU_METER_KERNEL ; 
 size_t CPU_METER_NICE ; 
 size_t CPU_METER_NORMAL ; 
 size_t CPU_STATE_MAX ; 
 size_t CPU_STATE_NICE ; 
 size_t CPU_STATE_SYSTEM ; 
 size_t CPU_STATE_USER ; 
 int /*<<< orphan*/  Meter_setItems (TYPE_2__*,int) ; 
 double Platform_setCPUAverageValues (TYPE_2__*) ; 

double Platform_setCPUValues(Meter* mtr, int cpu) {

   if (cpu == 0) {
      return Platform_setCPUAverageValues(mtr);
   }

   DarwinProcessList *dpl = (DarwinProcessList *)mtr->pl;
   processor_cpu_load_info_t prev = &dpl->prev_load[cpu-1];
   processor_cpu_load_info_t curr = &dpl->curr_load[cpu-1];
   double total = 0;

   /* Take the sums */
   for(size_t i = 0; i < CPU_STATE_MAX; ++i) {
      total += (double)curr->cpu_ticks[i] - (double)prev->cpu_ticks[i];
   }

   mtr->values[CPU_METER_NICE]
           = ((double)curr->cpu_ticks[CPU_STATE_NICE] - (double)prev->cpu_ticks[CPU_STATE_NICE])* 100.0 / total;
   mtr->values[CPU_METER_NORMAL]
           = ((double)curr->cpu_ticks[CPU_STATE_USER] - (double)prev->cpu_ticks[CPU_STATE_USER])* 100.0 / total;
   mtr->values[CPU_METER_KERNEL]
           = ((double)curr->cpu_ticks[CPU_STATE_SYSTEM] - (double)prev->cpu_ticks[CPU_STATE_SYSTEM])* 100.0 / total;

   Meter_setItems(mtr, 3);

   /* Convert to percent and return */
   total = mtr->values[CPU_METER_NICE] + mtr->values[CPU_METER_NORMAL] + mtr->values[CPU_METER_KERNEL];

   return CLAMP(total, 0.0, 100.0);
}