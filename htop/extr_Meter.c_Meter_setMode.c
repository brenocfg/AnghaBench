#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int mode; int /*<<< orphan*/  h; int /*<<< orphan*/  draw; int /*<<< orphan*/ * drawData; } ;
struct TYPE_9__ {int /*<<< orphan*/  h; int /*<<< orphan*/  draw; } ;
typedef  TYPE_1__ MeterMode ;
typedef  TYPE_2__ Meter ;

/* Variables and functions */
 scalar_t__ CUSTOM_METERMODE ; 
 int LAST_METERMODE ; 
 scalar_t__ Meter_defaultMode (TYPE_2__*) ; 
 int /*<<< orphan*/  Meter_drawFn (TYPE_2__*) ; 
 TYPE_1__** Meter_modes ; 
 int /*<<< orphan*/  Meter_updateMode (TYPE_2__*,int) ; 
 scalar_t__ Meter_updateModeFn (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void Meter_setMode(Meter* this, int modeIndex) {
   if (modeIndex > 0 && modeIndex == this->mode)
      return;
   if (!modeIndex)
      modeIndex = 1;
   assert(modeIndex < LAST_METERMODE);
   if (Meter_defaultMode(this) == CUSTOM_METERMODE) {
      this->draw = Meter_drawFn(this);
      if (Meter_updateModeFn(this))
         Meter_updateMode(this, modeIndex);
   } else {
      assert(modeIndex >= 1);
      free(this->drawData);
      this->drawData = NULL;

      MeterMode* mode = Meter_modes[modeIndex];
      this->draw = mode->draw;
      this->h = mode->h;
   }
   this->mode = modeIndex;
}