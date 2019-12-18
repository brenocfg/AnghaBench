#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int h; } ;
struct TYPE_7__ {int mode; int h; scalar_t__ drawData; } ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  AllCPUsMeter_getRange (TYPE_1__*,int*,int*) ; 
 TYPE_4__** Meter_modes ; 
 int /*<<< orphan*/  Meter_name (TYPE_1__*) ; 
 int /*<<< orphan*/  Meter_setMode (TYPE_1__*,int) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void AllCPUsMeter_updateMode(Meter* this, int mode) {
   Meter** meters = (Meter**) this->drawData;
   this->mode = mode;
   int h = Meter_modes[mode]->h;
   int start, count;
   AllCPUsMeter_getRange(this, &start, &count);
   for (int i = 0; i < count; i++) {
      Meter_setMode(meters[i], mode);
   }
   if (strchr(Meter_name(this), '2'))
      this->h = h * ((count+1) / 2);
   else
      this->h = h * count;
}