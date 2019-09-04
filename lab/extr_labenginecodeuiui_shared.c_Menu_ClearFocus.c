#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int itemCount; TYPE_3__** items; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_7__ {int flags; } ;
struct TYPE_9__ {scalar_t__ leaveFocus; TYPE_1__ window; } ;
typedef  TYPE_3__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_RunScript (TYPE_3__*,scalar_t__) ; 
 int WINDOW_HASFOCUS ; 

itemDef_t *Menu_ClearFocus(menuDef_t *menu) {
  int i;
  itemDef_t *ret = NULL;

  if (menu == NULL) {
    return NULL;
  }

  for (i = 0; i < menu->itemCount; i++) {
    if (menu->items[i]->window.flags & WINDOW_HASFOCUS) {
      ret = menu->items[i];
    } 
    menu->items[i]->window.flags &= ~WINDOW_HASFOCUS;
    if (menu->items[i]->leaveFocus) {
      Item_RunScript(menu->items[i], menu->items[i]->leaveFocus);
    }
  }
 
  return ret;
}