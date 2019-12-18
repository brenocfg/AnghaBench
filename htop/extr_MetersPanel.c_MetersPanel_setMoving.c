#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int moving; } ;
struct TYPE_9__ {int /*<<< orphan*/  currentBar; } ;
struct TYPE_11__ {int moving; TYPE_1__ super; } ;
struct TYPE_10__ {int /*<<< orphan*/  currentBar; } ;
typedef  TYPE_2__ Panel ;
typedef  TYPE_3__ MetersPanel ;
typedef  TYPE_4__ ListItem ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 int /*<<< orphan*/  FunctionBar_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Meters_movingBar ; 
 size_t PANEL_SELECTION_FOCUS ; 
 size_t PANEL_SELECTION_FOLLOW ; 
 scalar_t__ Panel_getSelected (TYPE_2__*) ; 
 int /*<<< orphan*/  Panel_setDefaultBar (TYPE_2__*) ; 
 int /*<<< orphan*/  Panel_setSelectionColor (TYPE_2__*,int /*<<< orphan*/ ) ; 

void MetersPanel_setMoving(MetersPanel* this, bool moving) {
   Panel* super = (Panel*) this;
   this->moving = moving;
   ListItem* selected = (ListItem*)Panel_getSelected(super);
   if (selected) {
      selected->moving = moving;
   }
   if (!moving) {
      Panel_setSelectionColor(super, CRT_colors[PANEL_SELECTION_FOCUS]);
      Panel_setDefaultBar(super);
   } else {
      Panel_setSelectionColor(super, CRT_colors[PANEL_SELECTION_FOLLOW]);
      super->currentBar = Meters_movingBar;
   }
   FunctionBar_draw(this->super.currentBar, NULL);
}