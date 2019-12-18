#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int h; } ;
struct TYPE_10__ {int cpuCount; } ;
struct TYPE_9__ {size_t mode; int h; TYPE_3__* pl; scalar_t__ drawData; } ;
typedef  int /*<<< orphan*/  MeterClass ;
typedef  TYPE_1__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  AllCPUsMeter_getRange (TYPE_1__*,int*,int*) ; 
 size_t BAR_METERMODE ; 
 int /*<<< orphan*/  CPUMeter ; 
 scalar_t__ Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Meter_init (TYPE_1__*) ; 
 TYPE_5__** Meter_modes ; 
 int /*<<< orphan*/  Meter_name (TYPE_1__*) ; 
 TYPE_1__* Meter_new (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ xCalloc (int,int) ; 

__attribute__((used)) static void AllCPUsMeter_init(Meter* this) {
   int cpus = this->pl->cpuCount;
   if (!this->drawData)
      this->drawData = xCalloc(cpus, sizeof(Meter*));
   Meter** meters = (Meter**) this->drawData;
   int start, count;
   AllCPUsMeter_getRange(this, &start, &count);
   for (int i = 0; i < count; i++) {
      if (!meters[i])
         meters[i] = Meter_new(this->pl, start+i+1, (MeterClass*) Class(CPUMeter));
      Meter_init(meters[i]);
   }
   if (this->mode == 0)
      this->mode = BAR_METERMODE;
   int h = Meter_modes[this->mode]->h;
   if (strchr(Meter_name(this), '2'))
      this->h = h * ((count+1) / 2);
   else
      this->h = h * count;
}