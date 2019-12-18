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
struct TYPE_3__ {int /*<<< orphan*/  pl; int /*<<< orphan*/ ** columns; } ;
typedef  int /*<<< orphan*/  MeterClass ;
typedef  int /*<<< orphan*/  Meter ;
typedef  TYPE_1__ Header ;

/* Variables and functions */
 int /*<<< orphan*/ * Meter_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Meter* Header_addMeterByClass(Header* this, MeterClass* type, int param, int column) {
   Vector* meters = this->columns[column];

   Meter* meter = Meter_new(this->pl, param, type);
   Vector_add(meters, meter);
   return meter;
}