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
struct TYPE_3__ {int panelCount; int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ ScreenManager ;
typedef  int /*<<< orphan*/  Panel ;

/* Variables and functions */
 scalar_t__ Vector_remove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 

Panel* ScreenManager_remove(ScreenManager* this, int idx) {
   assert(this->panelCount > idx);
   Panel* panel = (Panel*) Vector_remove(this->panels, idx);
   this->panelCount--;
   return panel;
}