#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ h; scalar_t__ w; scalar_t__ x; int /*<<< orphan*/  y; } ;
struct TYPE_5__ {int panelCount; scalar_t__ orientation; int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ ScreenManager ;
typedef  TYPE_2__ Panel ;

/* Variables and functions */
 scalar_t__ HORIZONTAL ; 
 int /*<<< orphan*/  Panel_draw (TYPE_2__*,int) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvvline (int /*<<< orphan*/ ,scalar_t__,char,scalar_t__) ; 

__attribute__((used)) static void ScreenManager_drawPanels(ScreenManager* this, int focus) {
   const int nPanels = this->panelCount;
   for (int i = 0; i < nPanels; i++) {
      Panel* panel = (Panel*) Vector_get(this->panels, i);
      Panel_draw(panel, i == focus);
      if (this->orientation == HORIZONTAL) {
         mvvline(panel->y, panel->x+panel->w, ' ', panel->h+1);
      }
   }
}