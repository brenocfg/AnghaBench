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
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ window; } ;
typedef  TYPE_2__ menuDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_RunCloseScript (TYPE_2__*) ; 
 TYPE_2__* Menus_FindByName (char const*) ; 
 int WINDOW_HASFOCUS ; 
 int WINDOW_VISIBLE ; 

void Menus_CloseByName(const char *p) {
  menuDef_t *menu = Menus_FindByName(p);
  if (menu != NULL) {
		Menu_RunCloseScript(menu);
		menu->window.flags &= ~(WINDOW_VISIBLE | WINDOW_HASFOCUS);
  }
}