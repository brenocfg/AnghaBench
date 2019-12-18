#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int x; int w; int needsRedraw; } ;
struct TYPE_8__ {scalar_t__ orientation; scalar_t__ panelCount; int y1; int y2; int x1; int x2; int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ ScreenManager ;
typedef  TYPE_2__ Panel ;

/* Variables and functions */
 int COLS ; 
 scalar_t__ HORIZONTAL ; 
 int LINES ; 
 int /*<<< orphan*/  Panel_move (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  Panel_resize (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  Vector_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,scalar_t__) ; 

void ScreenManager_add(ScreenManager* this, Panel* item, int size) {
   if (this->orientation == HORIZONTAL) {
      int lastX = 0;
      if (this->panelCount > 0) {
         Panel* last = (Panel*) Vector_get(this->panels, this->panelCount - 1);
         lastX = last->x + last->w + 1;
      }
      int height = LINES - this->y1 + this->y2;
      if (size > 0) {
         Panel_resize(item, size, height);
      } else {
         Panel_resize(item, COLS-this->x1+this->x2-lastX, height);
      }
      Panel_move(item, lastX, this->y1);
   }
   // TODO: VERTICAL
   Vector_add(this->panels, item);
   item->needsRedraw = true;
   this->panelCount++;
}