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
struct TYPE_3__ {int x; int y; int w; int h; int needsRedraw; int /*<<< orphan*/  selectionColor; int /*<<< orphan*/ * currentBar; int /*<<< orphan*/ * defaultBar; int /*<<< orphan*/  header; scalar_t__ oldSelected; scalar_t__ selected; scalar_t__ scrollH; scalar_t__ scrollV; int /*<<< orphan*/  items; int /*<<< orphan*/ * eventHandlerState; } ;
typedef  TYPE_1__ Panel ;
typedef  int /*<<< orphan*/  ObjectClass ;
typedef  int /*<<< orphan*/  FunctionBar ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 int /*<<< orphan*/  DEFAULT_SIZE ; 
 size_t PANEL_SELECTION_FOCUS ; 
 int /*<<< orphan*/  RichString_beginAllocated (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_new (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void Panel_init(Panel* this, int x, int y, int w, int h, ObjectClass* type, bool owner, FunctionBar* fuBar) {
   this->x = x;
   this->y = y;
   this->w = w;
   this->h = h;
   this->eventHandlerState = NULL;
   this->items = Vector_new(type, owner, DEFAULT_SIZE);
   this->scrollV = 0;
   this->scrollH = 0;
   this->selected = 0;
   this->oldSelected = 0;
   this->needsRedraw = true;
   RichString_beginAllocated(this->header);
   this->defaultBar = fuBar;
   this->currentBar = fuBar;
   this->selectionColor = CRT_colors[PANEL_SELECTION_FOCUS];
}