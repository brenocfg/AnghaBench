#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int totalPeriod; double nicePeriod; double userPeriod; double systemPeriod; double irqPeriod; double softIrqPeriod; double stealPeriod; double guestPeriod; double ioWaitPeriod; double systemAllPeriod; } ;
struct TYPE_11__ {TYPE_5__* cpus; } ;
struct TYPE_10__ {double* values; TYPE_2__* pl; } ;
struct TYPE_9__ {TYPE_1__* settings; } ;
struct TYPE_8__ {scalar_t__ accountGuestInCPUMeter; scalar_t__ detailedCPUTime; } ;
typedef  TYPE_3__ Meter ;
typedef  TYPE_4__ LinuxProcessList ;
typedef  TYPE_5__ CPUData ;

/* Variables and functions */
 double CLAMP (double,double,double) ; 
 size_t CPU_METER_GUEST ; 
 size_t CPU_METER_IOWAIT ; 
 size_t CPU_METER_IRQ ; 
 size_t CPU_METER_KERNEL ; 
 size_t CPU_METER_NICE ; 
 size_t CPU_METER_NORMAL ; 
 size_t CPU_METER_SOFTIRQ ; 
 size_t CPU_METER_STEAL ; 
 int /*<<< orphan*/  Meter_setItems (TYPE_3__*,int) ; 
 scalar_t__ isnan (double) ; 

double Platform_setCPUValues(Meter* this, int cpu) {
   LinuxProcessList* pl = (LinuxProcessList*) this->pl;
   CPUData* cpuData = &(pl->cpus[cpu]);
   double total = (double) ( cpuData->totalPeriod == 0 ? 1 : cpuData->totalPeriod);
   double percent;
   double* v = this->values;
   v[CPU_METER_NICE] = cpuData->nicePeriod / total * 100.0;
   v[CPU_METER_NORMAL] = cpuData->userPeriod / total * 100.0;
   if (this->pl->settings->detailedCPUTime) {
      v[CPU_METER_KERNEL]  = cpuData->systemPeriod / total * 100.0;
      v[CPU_METER_IRQ]     = cpuData->irqPeriod / total * 100.0;
      v[CPU_METER_SOFTIRQ] = cpuData->softIrqPeriod / total * 100.0;
      v[CPU_METER_STEAL]   = cpuData->stealPeriod / total * 100.0;
      v[CPU_METER_GUEST]   = cpuData->guestPeriod / total * 100.0;
      v[CPU_METER_IOWAIT]  = cpuData->ioWaitPeriod / total * 100.0;
      Meter_setItems(this, 8);
      if (this->pl->settings->accountGuestInCPUMeter) {
         percent = v[0]+v[1]+v[2]+v[3]+v[4]+v[5]+v[6];
      } else {
         percent = v[0]+v[1]+v[2]+v[3]+v[4];
      }
   } else {
      v[2] = cpuData->systemAllPeriod / total * 100.0;
      v[3] = (cpuData->stealPeriod + cpuData->guestPeriod) / total * 100.0;
      Meter_setItems(this, 4);
      percent = v[0]+v[1]+v[2]+v[3];
   }
   percent = CLAMP(percent, 0.0, 100.0);
   if (isnan(percent)) percent = 0.0;
   return percent;
}