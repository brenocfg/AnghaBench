#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int x; int y; } ;
struct TYPE_9__ {int flags; TYPE_1__ rect; } ;
struct TYPE_10__ {TYPE_2__ window; } ;
typedef  TYPE_3__ menuDef_t ;

/* Variables and functions */
 TYPE_3__* Menu_GetFocused () ; 
 int /*<<< orphan*/  Menu_HandleMouseMove (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  Menu_UpdatePosition (TYPE_3__*) ; 
 TYPE_3__* Menus ; 
 int WINDOW_POPUP ; 
 int menuCount ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Display_MouseMove(void *p, int x, int y) {
	int i;
	menuDef_t *menu = p;

	if (menu == NULL) {
    menu = Menu_GetFocused();
		if (menu) {
			if (menu->window.flags & WINDOW_POPUP) {
				Menu_HandleMouseMove(menu, x, y);
				return qtrue;
			}
		}
		for (i = 0; i < menuCount; i++) {
			Menu_HandleMouseMove(&Menus[i], x, y);
		}
	} else {
		menu->window.rect.x += x;
		menu->window.rect.y += y;
		Menu_UpdatePosition(menu);
	}
 	return qtrue;

}