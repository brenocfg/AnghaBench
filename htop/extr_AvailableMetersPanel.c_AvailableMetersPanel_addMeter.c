#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  currentBar; } ;
typedef  TYPE_1__ Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  MetersPanel ;
typedef  int /*<<< orphan*/  MeterClass ;
typedef  int /*<<< orphan*/  Meter ;
typedef  int /*<<< orphan*/  Header ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Header_addMeterByClass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ Meter_toListItem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MetersPanel_setMoving (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Panel_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Panel_setSelected (TYPE_1__*,scalar_t__) ; 
 scalar_t__ Panel_size (TYPE_1__*) ; 

__attribute__((used)) static inline void AvailableMetersPanel_addMeter(Header* header, Panel* panel, MeterClass* type, int param, int column) {
   Meter* meter = (Meter*) Header_addMeterByClass(header, type, param, column);
   Panel_add(panel, (Object*) Meter_toListItem(meter, false));
   Panel_setSelected(panel, Panel_size(panel) - 1);
   MetersPanel_setMoving((MetersPanel*)panel, true);
   FunctionBar_draw(panel->currentBar, NULL);
}