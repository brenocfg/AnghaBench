#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menuDef_t ;
struct TYPE_8__ {float x; float y; } ;
struct TYPE_7__ {float x; float y; } ;
struct TYPE_9__ {int flags; int offsetTime; TYPE_2__ rectClient; TYPE_1__ rectEffects; } ;
struct TYPE_10__ {TYPE_3__ window; } ;
typedef  TYPE_4__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_UpdatePosition (TYPE_4__*) ; 
 TYPE_4__* Menu_GetMatchingItemByNumber (int /*<<< orphan*/ *,int,char const*) ; 
 int Menu_ItemsMatchingGroup (int /*<<< orphan*/ *,char const*) ; 
 int WINDOW_ORBITING ; 
 int WINDOW_VISIBLE ; 

void Menu_OrbitItemByName(menuDef_t *menu, const char *p, float x, float y, float cx, float cy, int time) {
  itemDef_t *item;
  int i;
  int count = Menu_ItemsMatchingGroup(menu, p);
  for (i = 0; i < count; i++) {
    item = Menu_GetMatchingItemByNumber(menu, i, p);
    if (item != NULL) {
      item->window.flags |= (WINDOW_ORBITING | WINDOW_VISIBLE);
      item->window.offsetTime = time;
      item->window.rectEffects.x = cx;
      item->window.rectEffects.y = cy;
      item->window.rectClient.x = x;
      item->window.rectClient.y = y;
      Item_UpdatePosition(item);
    }
  }
}