#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int menusp; int /*<<< orphan*/  firstdraw; int /*<<< orphan*/ * stack; int /*<<< orphan*/  activemenu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  menu_out_sound ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Error (char*) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ uis ; 

void UI_PopMenu (void)
{
	trap_S_StartLocalSound( menu_out_sound, CHAN_LOCAL_SOUND );

	uis.menusp--;

	if (uis.menusp < 0)
		trap_Error ("UI_PopMenu: menu stack underflow");

	if (uis.menusp) {
		uis.activemenu = uis.stack[uis.menusp-1];
		uis.firstdraw = qtrue;
	}
	else {
		UI_ForceMenuOff ();
	}
}