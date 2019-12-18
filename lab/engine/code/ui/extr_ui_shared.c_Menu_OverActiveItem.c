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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  rect; } ;
struct TYPE_9__ {int itemCount; TYPE_4__** items; TYPE_1__ window; } ;
typedef  TYPE_3__ menuDef_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  rect; } ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ text; TYPE_2__ window; } ;
typedef  TYPE_4__ itemDef_t ;

/* Variables and functions */
 scalar_t__ ITEM_TYPE_TEXT ; 
 int /*<<< orphan*/ * Item_CorrectedTextRect (TYPE_4__*) ; 
 scalar_t__ Rect_ContainsPoint (int /*<<< orphan*/ *,float,float) ; 
 int WINDOW_DECORATION ; 
 int WINDOW_FORCED ; 
 int WINDOW_VISIBLE ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean Menu_OverActiveItem(menuDef_t *menu, float x, float y) {
 	if (menu && menu->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED)) {
		if (Rect_ContainsPoint(&menu->window.rect, x, y)) {
			int i;
			for (i = 0; i < menu->itemCount; i++) {
				// turn off focus each item
				// menu->items[i].window.flags &= ~WINDOW_HASFOCUS;

				if (!(menu->items[i]->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED))) {
					continue;
				}

				if (menu->items[i]->window.flags & WINDOW_DECORATION) {
					continue;
				}

				if (Rect_ContainsPoint(&menu->items[i]->window.rect, x, y)) {
					itemDef_t *overItem = menu->items[i];
					if (overItem->type == ITEM_TYPE_TEXT && overItem->text) {
						if (Rect_ContainsPoint(Item_CorrectedTextRect(overItem), x, y)) {
							return qtrue;
						} else {
							continue;
						}
					} else {
						return qtrue;
					}
				}
			}

		}
	}
	return qfalse;
}