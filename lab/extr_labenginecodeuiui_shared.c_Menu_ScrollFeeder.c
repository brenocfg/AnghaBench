#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {int itemCount; TYPE_3__** items; } ;
typedef  TYPE_1__ menuDef_t ;
struct TYPE_5__ {int special; } ;

/* Variables and functions */
 int /*<<< orphan*/  Item_ListBox_HandleKey (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K_DOWNARROW ; 
 int /*<<< orphan*/  K_UPARROW ; 
 int /*<<< orphan*/  qtrue ; 

void Menu_ScrollFeeder(menuDef_t *menu, int feeder, qboolean down) {
	if (menu) {
		int i;
    for (i = 0; i < menu->itemCount; i++) {
			if (menu->items[i]->special == feeder) {
				Item_ListBox_HandleKey(menu->items[i], (down) ? K_DOWNARROW : K_UPARROW, qtrue, qtrue);
				return;
			}
		}
	}
}