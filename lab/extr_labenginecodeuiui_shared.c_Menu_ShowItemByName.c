#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  menuDef_t ;
struct TYPE_5__ {int cinematic; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* stopCinematic ) (int) ;} ;

/* Variables and functions */
 TYPE_4__* DC ; 
 TYPE_2__* Menu_GetMatchingItemByNumber (int /*<<< orphan*/ *,int,char const*) ; 
 int Menu_ItemsMatchingGroup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  WINDOW_VISIBLE ; 
 int /*<<< orphan*/  stub1 (int) ; 

void Menu_ShowItemByName(menuDef_t *menu, const char *p, qboolean bShow) {
	itemDef_t *item;
	int i;
	int count = Menu_ItemsMatchingGroup(menu, p);
	for (i = 0; i < count; i++) {
		item = Menu_GetMatchingItemByNumber(menu, i, p);
		if (item != NULL) {
			if (bShow) {
				item->window.flags |= WINDOW_VISIBLE;
			} else {
				item->window.flags &= ~WINDOW_VISIBLE;
				// stop cinematics playing in the window
				if (item->window.cinematic >= 0) {
					DC->stopCinematic(item->window.cinematic);
					item->window.cinematic = -1;
				}
			}
		}
	}
}