#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* active; TYPE_1__* modes; } ;
struct TYPE_7__ {int /*<<< orphan*/  currentBar; } ;
struct TYPE_6__ {int /*<<< orphan*/  bar; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ Panel ;
typedef  size_t IncType ;
typedef  TYPE_3__ IncSet ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void IncSet_activate(IncSet* this, IncType type, Panel* panel) {
   this->active = &(this->modes[type]);
   FunctionBar_draw(this->active->bar, this->active->buffer);
   panel->currentBar = this->active->bar;
}