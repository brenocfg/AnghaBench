#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* values; scalar_t__ total; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  Platform_getLoadAverage (scalar_t__*,double*,double*) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static void LoadMeter_updateValues(Meter* this, char* buffer, int size) {
   double five, fifteen;
   Platform_getLoadAverage(&this->values[0], &five, &fifteen);
   if (this->values[0] > this->total) {
      this->total = this->values[0];
   }
   xSnprintf(buffer, size, "%.2f", this->values[0]);
}