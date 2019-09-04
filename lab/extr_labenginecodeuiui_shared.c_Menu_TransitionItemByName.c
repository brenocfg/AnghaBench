#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ h; scalar_t__ w; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ rectDef_t ;
typedef  int /*<<< orphan*/  menuDef_t ;
struct TYPE_10__ {float x; float y; float w; float h; } ;
struct TYPE_11__ {int flags; int offsetTime; TYPE_1__ rectEffects2; int /*<<< orphan*/  rectEffects; int /*<<< orphan*/  rectClient; } ;
struct TYPE_13__ {TYPE_2__ window; } ;
typedef  TYPE_4__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_UpdatePosition (TYPE_4__*) ; 
 TYPE_4__* Menu_GetMatchingItemByNumber (int /*<<< orphan*/ *,int,char const*) ; 
 int Menu_ItemsMatchingGroup (int /*<<< orphan*/ *,char const*) ; 
 int WINDOW_INTRANSITION ; 
 int WINDOW_VISIBLE ; 
 float fabs (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

void Menu_TransitionItemByName(menuDef_t *menu, const char *p, rectDef_t rectFrom, rectDef_t rectTo, int time, float amt) {
  itemDef_t *item;
  int i;
  int count = Menu_ItemsMatchingGroup(menu, p);
  for (i = 0; i < count; i++) {
    item = Menu_GetMatchingItemByNumber(menu, i, p);
    if (item != NULL) {
      item->window.flags |= (WINDOW_INTRANSITION | WINDOW_VISIBLE);
      item->window.offsetTime = time;
			memcpy(&item->window.rectClient, &rectFrom, sizeof(rectDef_t));
			memcpy(&item->window.rectEffects, &rectTo, sizeof(rectDef_t));
			item->window.rectEffects2.x = fabs(rectTo.x - rectFrom.x) / amt;
			item->window.rectEffects2.y = fabs(rectTo.y - rectFrom.y) / amt;
			item->window.rectEffects2.w = fabs(rectTo.w - rectFrom.w) / amt;
			item->window.rectEffects2.h = fabs(rectTo.h - rectFrom.h) / amt;
      Item_UpdatePosition(item);
    }
  }
}