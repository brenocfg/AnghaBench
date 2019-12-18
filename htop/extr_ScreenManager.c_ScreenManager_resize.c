#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int w; int x; } ;
struct TYPE_6__ {int x1; int y1; int x2; int y2; int panelCount; scalar_t__ orientation; int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ ScreenManager ;
typedef  TYPE_2__ Panel ;

/* Variables and functions */
 int COLS ; 
 scalar_t__ HORIZONTAL ; 
 int LINES ; 
 int /*<<< orphan*/  Panel_move (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  Panel_resize (TYPE_2__*,int,int) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,int) ; 

void ScreenManager_resize(ScreenManager* this, int x1, int y1, int x2, int y2) {
   this->x1 = x1;
   this->y1 = y1;
   this->x2 = x2;
   this->y2 = y2;
   int panels = this->panelCount;
   if (this->orientation == HORIZONTAL) {
      int lastX = 0;
      for (int i = 0; i < panels - 1; i++) {
         Panel* panel = (Panel*) Vector_get(this->panels, i);
         Panel_resize(panel, panel->w, LINES-y1+y2);
         Panel_move(panel, lastX, y1);
         lastX = panel->x + panel->w + 1;
      }
      Panel* panel = (Panel*) Vector_get(this->panels, panels-1);
      Panel_resize(panel, COLS-x1+x2-lastX, LINES-y1+y2);
      Panel_move(panel, lastX, y1);
   }
   // TODO: VERTICAL
}