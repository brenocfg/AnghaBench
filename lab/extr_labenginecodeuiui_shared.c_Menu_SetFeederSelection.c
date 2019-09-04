#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int itemCount; TYPE_1__** items; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_10__ {scalar_t__ startPos; scalar_t__ cursorPos; } ;
typedef  TYPE_3__ listBoxDef_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* feederSelection ) (int,int) ;} ;
struct TYPE_8__ {int special; int cursorPos; scalar_t__ typeData; } ;

/* Variables and functions */
 TYPE_7__* DC ; 
 TYPE_2__* Menu_GetFocused () ; 
 TYPE_2__* Menus_FindByName (char const*) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 

void Menu_SetFeederSelection(menuDef_t *menu, int feeder, int index, const char *name) {
	if (menu == NULL) {
		if (name == NULL) {
			menu = Menu_GetFocused();
		} else {
			menu = Menus_FindByName(name);
		}
	}

	if (menu) {
		int i;
    for (i = 0; i < menu->itemCount; i++) {
			if (menu->items[i]->special == feeder) {
				if (index == 0) {
					listBoxDef_t *listPtr = (listBoxDef_t*)menu->items[i]->typeData;
					listPtr->cursorPos = 0;
					listPtr->startPos = 0;
				}
				menu->items[i]->cursorPos = index;
				DC->feederSelection(menu->items[i]->special, menu->items[i]->cursorPos);
				return;
			}
		}
	}
}