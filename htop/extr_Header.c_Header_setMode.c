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
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_3__ {int /*<<< orphan*/ ** columns; } ;
typedef  int /*<<< orphan*/  MeterModeId ;
typedef  int /*<<< orphan*/  Meter ;
typedef  TYPE_1__ Header ;

/* Variables and functions */
 int /*<<< orphan*/  Meter_setMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ *,int) ; 
 int Vector_size (int /*<<< orphan*/ *) ; 

void Header_setMode(Header* this, int i, MeterModeId mode, int column) {
   Vector* meters = this->columns[column];

   if (i >= Vector_size(meters))
      return;
   Meter* meter = (Meter*) Vector_get(meters, i);
   Meter_setMode(meter, mode);
}