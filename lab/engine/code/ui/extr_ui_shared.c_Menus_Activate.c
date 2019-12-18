#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {scalar_t__* soundName; scalar_t__ onOpen; TYPE_1__ window; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_9__ {TYPE_2__* parent; } ;
typedef  TYPE_3__ itemDef_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* startBackgroundTrack ) (scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 TYPE_6__* DC ; 
 int /*<<< orphan*/  Display_CloseCinematics () ; 
 int /*<<< orphan*/  Item_RunScript (TYPE_3__*,scalar_t__) ; 
 int WINDOW_HASFOCUS ; 
 int WINDOW_VISIBLE ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,scalar_t__*) ; 

void  Menus_Activate(menuDef_t *menu) {
	menu->window.flags |= (WINDOW_HASFOCUS | WINDOW_VISIBLE);
	if (menu->onOpen) {
		itemDef_t item;
		item.parent = menu;
		Item_RunScript(&item, menu->onOpen);
	}

	if (menu->soundName && *menu->soundName) {
//		DC->stopBackgroundTrack();					// you don't want to do this since it will reset s_rawend
		DC->startBackgroundTrack(menu->soundName, menu->soundName);
	}

	Display_CloseCinematics();

}