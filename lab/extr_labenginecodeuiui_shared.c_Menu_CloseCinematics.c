#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ownerDraw; } ;
struct TYPE_7__ {int itemCount; TYPE_1__** items; TYPE_3__ window; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* stopCinematic ) (scalar_t__) ;} ;
struct TYPE_6__ {scalar_t__ type; TYPE_3__ window; } ;

/* Variables and functions */
 TYPE_5__* DC ; 
 scalar_t__ ITEM_TYPE_OWNERDRAW ; 
 int /*<<< orphan*/  Window_CloseCinematic (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void Menu_CloseCinematics(menuDef_t *menu) {
	if (menu) {
		int i;
		Window_CloseCinematic(&menu->window);
	  for (i = 0; i < menu->itemCount; i++) {
		  Window_CloseCinematic(&menu->items[i]->window);
			if (menu->items[i]->type == ITEM_TYPE_OWNERDRAW) {
				DC->stopCinematic(0-menu->items[i]->window.ownerDraw);
			}
	  }
	}
}