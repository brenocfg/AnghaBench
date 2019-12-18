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
struct TYPE_6__ {int cpuCount; } ;
struct TYPE_8__ {TYPE_1__ super; } ;
struct TYPE_7__ {double* values; scalar_t__ pl; } ;
typedef  TYPE_2__ Meter ;
typedef  TYPE_3__ DarwinProcessList ;

/* Variables and functions */
 size_t CPU_METER_KERNEL ; 
 size_t CPU_METER_NICE ; 
 size_t CPU_METER_NORMAL ; 
 scalar_t__ Platform_setCPUValues (TYPE_2__*,int) ; 

__attribute__((used)) static double Platform_setCPUAverageValues(Meter* mtr) {
   DarwinProcessList *dpl = (DarwinProcessList *)mtr->pl;
   int cpus = dpl->super.cpuCount;
   double sumNice = 0.0;
   double sumNormal = 0.0;
   double sumKernel = 0.0;
   double sumPercent = 0.0;
   for (int i = 1; i <= cpus; i++) {
      sumPercent += Platform_setCPUValues(mtr, i);
      sumNice    += mtr->values[CPU_METER_NICE];
      sumNormal  += mtr->values[CPU_METER_NORMAL];
      sumKernel  += mtr->values[CPU_METER_KERNEL];
   }
   mtr->values[CPU_METER_NICE]   = sumNice   / cpus;
   mtr->values[CPU_METER_NORMAL] = sumNormal / cpus;
   mtr->values[CPU_METER_KERNEL] = sumKernel / cpus;
   return sumPercent / cpus;
}