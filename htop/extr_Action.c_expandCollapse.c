#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int showChildren; } ;
typedef  TYPE_1__ Process ;
typedef  int /*<<< orphan*/  Panel ;

/* Variables and functions */
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool expandCollapse(Panel* panel) {
   Process* p = (Process*) Panel_getSelected(panel);
   if (!p) return false;
   p->showChildren = !p->showChildren;
   return true;
}