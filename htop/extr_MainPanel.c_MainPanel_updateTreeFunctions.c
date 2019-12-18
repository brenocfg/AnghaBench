#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MainPanel ;
typedef  int /*<<< orphan*/  FunctionBar ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_setLabel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEY_F (int) ; 
 int /*<<< orphan*/ * MainPanel_getFunctionBar (int /*<<< orphan*/ *) ; 

void MainPanel_updateTreeFunctions(MainPanel* this, bool mode) {
   FunctionBar* bar = MainPanel_getFunctionBar(this);
   if (mode) {
      FunctionBar_setLabel(bar, KEY_F(5), "Sorted");
      FunctionBar_setLabel(bar, KEY_F(6), "Collap");
   } else {
      FunctionBar_setLabel(bar, KEY_F(5), "Tree  ");
      FunctionBar_setLabel(bar, KEY_F(6), "SortBy");
   }
}