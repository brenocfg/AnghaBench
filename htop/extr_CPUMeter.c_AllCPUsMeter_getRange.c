#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pl; } ;
struct TYPE_5__ {int cpuCount; } ;
typedef  TYPE_2__ Meter ;

/* Variables and functions */
 int* Meter_name (TYPE_2__*) ; 

__attribute__((used)) static void AllCPUsMeter_getRange(Meter* this, int* start, int* count) {
   int cpus = this->pl->cpuCount;
   switch(Meter_name(this)[0]) {
      default:
      case 'A': // All
         *start = 0;
         *count = cpus;
         break;
      case 'L': // First Half
         *start = 0;
         *count = (cpus+1) / 2;
         break;
      case 'R': // Second Half
         *start = (cpus+1) / 2;
         *count = cpus / 2;
         break;
   }
}