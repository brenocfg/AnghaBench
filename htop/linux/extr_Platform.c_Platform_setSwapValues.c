#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * values; int /*<<< orphan*/  total; scalar_t__ pl; } ;
struct TYPE_4__ {int /*<<< orphan*/  usedSwap; int /*<<< orphan*/  totalSwap; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ Meter ;

/* Variables and functions */

void Platform_setSwapValues(Meter* this) {
   ProcessList* pl = (ProcessList*) this->pl;
   this->total = pl->totalSwap;
   this->values[0] = pl->usedSwap;
}