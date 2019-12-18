#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ProcessList_ {int dummy; } ;
struct TYPE_11__ {int h; int param; int /*<<< orphan*/  caption; int /*<<< orphan*/  total; void* values; struct ProcessList_* pl; } ;
struct TYPE_10__ {int curItems; int maxItems; int /*<<< orphan*/  defaultMode; int /*<<< orphan*/  caption; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ MeterClass ;
typedef  TYPE_2__ Meter ;

/* Variables and functions */
 int /*<<< orphan*/  Meter_init (TYPE_2__*) ; 
 scalar_t__ Meter_initFn (TYPE_2__*) ; 
 int /*<<< orphan*/  Meter_setMode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Object_setClass (TYPE_2__*,TYPE_1__*) ; 
 void* xCalloc (int,int) ; 
 int /*<<< orphan*/  xStrdup (int /*<<< orphan*/ ) ; 

Meter* Meter_new(struct ProcessList_* pl, int param, MeterClass* type) {
   Meter* this = xCalloc(1, sizeof(Meter));
   Object_setClass(this, type);
   this->h = 1;
   this->param = param;
   this->pl = pl;
   type->curItems = type->maxItems;
   this->values = xCalloc(type->maxItems, sizeof(double));
   this->total = type->total;
   this->caption = xStrdup(type->caption);
   if (Meter_initFn(this))
      Meter_init(this);
   Meter_setMode(this, type->defaultMode);
   return this;
}