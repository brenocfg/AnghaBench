#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ window; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* Pause ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  cursory; int /*<<< orphan*/  cursorx; } ;

/* Variables and functions */
 TYPE_5__* DC ; 
 int /*<<< orphan*/  Display_CloseCinematics () ; 
 scalar_t__ Display_VisibleMenuCount () ; 
 int /*<<< orphan*/  Menu_HandleKey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Menu_HandleMouseMove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Menu_OverActiveItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Menu_RunCloseScript (TYPE_2__*) ; 
 int /*<<< orphan*/ * Menus ; 
 int /*<<< orphan*/  Menus_Activate (int /*<<< orphan*/ *) ; 
 int WINDOW_HASFOCUS ; 
 int WINDOW_OOB_CLICK ; 
 int WINDOW_VISIBLE ; 
 int menuCount ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void Menus_HandleOOBClick(menuDef_t *menu, int key, qboolean down) {
	if (menu) {
		int i;
		// basically the behaviour we are looking for is if there are windows in the stack.. see if 
		// the cursor is within any of them.. if not close them otherwise activate them and pass the 
		// key on.. force a mouse move to activate focus and script stuff 
		if (down && menu->window.flags & WINDOW_OOB_CLICK) {
			Menu_RunCloseScript(menu);
			menu->window.flags &= ~(WINDOW_HASFOCUS | WINDOW_VISIBLE);
		}

		for (i = 0; i < menuCount; i++) {
			if (Menu_OverActiveItem(&Menus[i], DC->cursorx, DC->cursory)) {
				Menu_RunCloseScript(menu);
				menu->window.flags &= ~(WINDOW_HASFOCUS | WINDOW_VISIBLE);
				Menus_Activate(&Menus[i]);
				Menu_HandleMouseMove(&Menus[i], DC->cursorx, DC->cursory);
				Menu_HandleKey(&Menus[i], key, down);
			}
		}

		if (Display_VisibleMenuCount() == 0) {
			if (DC->Pause) {
				DC->Pause(qfalse);
			}
		}
		Display_CloseCinematics();
	}
}