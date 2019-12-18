#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int itemCount; TYPE_3__** items; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_6__ {scalar_t__ group; scalar_t__ name; } ;
struct TYPE_8__ {TYPE_1__ window; } ;
typedef  TYPE_3__ itemDef_t ;

/* Variables and functions */
 scalar_t__ Q_stricmp (scalar_t__,char const*) ; 

itemDef_t *Menu_GetMatchingItemByNumber(menuDef_t *menu, int index, const char *name) {
  int i;
  int count = 0;
  for (i = 0; i < menu->itemCount; i++) {
    if (Q_stricmp(menu->items[i]->window.name, name) == 0 || (menu->items[i]->window.group && Q_stricmp(menu->items[i]->window.group, name) == 0)) {
      if (count == index) {
        return menu->items[i];
      }
      count++;
    } 
  }
  return NULL;
}