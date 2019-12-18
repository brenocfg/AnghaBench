#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  menu; } ;
struct TYPE_3__ {int cursorx; int cursory; scalar_t__ menusp; } ;

/* Variables and functions */
 int /*<<< orphan*/  InGame_MenuInit () ; 
 int /*<<< orphan*/  UI_PushMenu (int /*<<< orphan*/ *) ; 
 TYPE_2__ s_ingame ; 
 TYPE_1__ uis ; 

void UI_InGameMenu( void ) {
	// force as top level menu
	uis.menusp = 0;  

	// set menu cursor to a nice location
	uis.cursorx = 319;
	uis.cursory = 80;

	InGame_MenuInit();
	UI_PushMenu( &s_ingame.menu );
}