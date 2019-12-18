#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ drawData; } ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  AllCPUsMeter_getRange (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  Meter_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AllCPUsMeter_done(Meter* this) {
   Meter** meters = (Meter**) this->drawData;
   int start, count;
   AllCPUsMeter_getRange(this, &start, &count);
   for (int i = 0; i < count; i++)
      Meter_delete((Object*)meters[i]);
}